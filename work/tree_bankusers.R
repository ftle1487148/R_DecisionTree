#####################################################################
#     rpart為遞迴分割法(Recursive Partitioning Tree)的縮寫          #
#  是一種CART(Classification and Regression Tree)決策樹演算法       #
#####################################################################
#install.packages("rpart")
library(rpart)
library("AER")

#載入creditcard資料集含1,319筆觀察測試，12個變數)
data(CreditCard)

#只要以下欄位(card:是否核准卡片、信用貶弱報告數、年齡、收入(美金)、自有住宅狀況、往來年月)
data <- subset(CreditCard, select = c(card, reports, age, income, owner, months))


#將是否核准卡片轉換為0/1數值
data$card <- ifelse(data$card == "yes", 1, 0);


#隨便給個種子
set.seed(1117)



#=============== 將資料分成訓練資料(70%)與預測資料(30%) ===============
#Decision tree是Supervised Learning(監督是學習)方法
#建議用sample函數將數據打散，數據訓練結果會比較好
#當訓練資料集內的數目太少，而變數太多時，分類的效果會變差
train.index <- sample(x=1:nrow(data), size=round(0.7*nrow(data))) #四捨五入
train <- data[train.index, ] #70%
test <- data[-train.index, ] #30%





################################ 建模過程分為兩階段 ################################
#1.長出最複雜的樹(grow the complex/full tree)。                                    #
#  (直到Leaf size樹葉內的觀測個數少於5個或是模型沒有優化的空間為止）               #
#2.使用交叉驗證(Cross Validation)來修剪樹(Prune)。                                 #
#  並尋找使估計風險值(estimate of risk)參數(complexity parameter)最小值的決策樹。  #
####################################################################################

#============================== rpart model 重要參數 ==============================
#weights:用來給與data的weight，如果想加重某些data的權重時可使用。 
#method：分成 “anova”、”poisson”、”class”和”exp”。目標變數為factor時，設定為”class”。
#parms：splitting function的參數，會根據上面不同的方法給不同的參數。(例如：”anova”方法是不需要參數的)
#control： rpart.control object (下面說明)
#大部分需要選擇的參數是weight與method

#-------------- rpart.control 重要參數 --------------
#minsplit：每一個node最少要幾個data
#minbucket：在末端的node上最少要幾個data
#cp：complexity parameter. (決定精度的參數)
#maxdepth：Tree的深度





#========== 建立各種模型 ========== 
#模型1：拿landmass以外的columns當作input預測landmass的條件變數
model<- rpart(card ~. , data=train, method = "class",control = rpart.control(cp = 0.001))

#模型2：基於模型1，樹深度2增加至4
modelx <- rpart(card ~., data=train,control=rpart.control(maxdepth=4,cp = 0.001), method = "class")



#==================== 繪圖 ====================
#1.內建plot指令
#僅能觀察到決策樹的判斷方式與結果
plot(model);text(model)


#2.套件:rpart.plot、函式:prp
#美觀但能呈現的訊息有限
#install.packages("rpart.plot")
library(rpart.plot)
rpart.plot(model,
           branch=1,             #branch=1：分支角度，0~1之間
           shadow.col="white",   #shadow.col：陰影顏色
           box.col="white",      #box.col：框內顏色
           border.col="black",   #border.col：框邊顏色
           split.col="red",      #split.col：分割條件顏色
           split.cex=1,          #split.cex：分割條件字型大小
           main="Decision tree"  #main：設定圖表名稱
)

# 每個Node節點上的數值分別代表:
#  a.預測類別
#  b.預測目標類別的機率(1的機率)
#  c.節點中觀測資料個數佔比


#prp()
prp(model,
    faclen=0,           # 呈現的變數不要縮寫
    fallen.leaves=TRUE, # 讓樹枝以垂直方式呈現
    shadow.col="gray",  # 最下面的節點塗上陰影
    extra=4)  
#節點下方分母意義 => number of correct classifications(正確分類的數量) / number of observations in that node(被分類但不管對錯的數量))


#3.套件:partykit 、函式: plot。
#葉節點透過可透過長條圖看到訓練集分布狀況
#install.packages("partykit")
library(partykit)
plot(as.party(model),cex = 1)


#4.套件:rattle、函式:fancyRpartPlot。
#透過不同色系進行呈現
#install.packages("rattle")
library("rattle")
fancyRpartPlot(model)





#====== 分析及預測 ======
rpart.rules(model,cover = TRUE)
#規則依照目標事件發生機率由低到高排序。
#cover：代表該節點觀測資料個數占比。



pred <- predict(model, newdata=test, type="class")
table(real=test$card, predict=pred)  #用table 交叉比對

#======== 計算預測準確率 = 對角線的數量/總數量 ========
confus.matrix <- table(real=test$card, predict=pred)
sum(diag(confus.matrix))/sum(confus.matrix) # 對角線的數量/總數量

printcp(model) #觀察未修剪的樹，CP欄位代表樹的成本複雜度參數
plotcp(model) #畫圖觀察
#隨著模型的複雜度（成本）增加，所能改善的模型適合度的空間降低(X-val relative error)。

#========= 修樹改進準確度 ========= 
prunetree_model <- prune(model, cp = model$cptable[which.min(model$cptable[,"xerror"]),"CP"]) # 利用能使決策樹具有最小誤差的CP來修剪樹

prunetree_pred <- predict(prunetree_model, newdata=test, type="class")

# 用table看預測的情況
table(real=test$card, predict=prunetree_pred)

confus.matrix <- table(real=test$card, predict=prunetree_pred)
sum(diag(confus.matrix))/sum(confus.matrix) # 對角線的數量/總數量
#準確率提升

#避免過度擬合，K-fold Cross-Validation，看最佳cp是多少
library("caret")
train_control <- trainControl(method="cv", number=10)
train_control.model <- train(card~., data=train, method="rpart", trControl=train_control)
train_control.model

