#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<typeinfo> 
#include<stdio.h>

using namespace std;

int personNumber; /* number of contact person */
class Contact_Management_System{
    public:
        string Gender;
        string Name;
        int PhoneNumber;
        string Email;
        string Address;
        string ContactPerson[50][5];
        int userSelect;
    
        void showMenu();
        void add();
        void list_all();
        void search();
        void edit();
        void delete_contact();
        void call_contact();
};

void Contact_Management_System :: showMenu(){
    cout << "***Welcome to Contact Management System ***" << endl;
    cout << "MAIN MENU" << endl;
    cout << "========================================" << endl;
    cout << "[1] Add a new Contact" << endl;
    cout << "[2] List all Contacts" << endl;
    cout << "[3] Search for contact" << endl;
    cout << "[4] Edit a Contact" << endl;
    cout << "[5] Delete a Contact" << endl;
    cout << "[6] Call the Contact" << endl;
    cout << "[0] Quit the Contact Management System" << endl;
    cout << "========================================" << endl;

}

void Contact_Management_System :: add(){
    cout << "enter gender: 0是男性，1是女性" << endl;
    cin >> ContactPerson[personNumber][0];
    cout << "enter name: " << endl;
    cin >> ContactPerson[personNumber][1];
    cout << "enter phone number: " << endl;
    cin >> ContactPerson[personNumber][2];
    cout << "enter email: " << endl;
    cin >> ContactPerson[personNumber][3];
    cout << "enter address: " << endl;
    cin >> ContactPerson[personNumber][4];
    cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "\t" << "address" << endl;
    cout << ContactPerson[personNumber][0] << "\t" <<ContactPerson[personNumber][1] << "\t" << ContactPerson[personNumber][2] << "\t" << ContactPerson[personNumber][3] << "\t" << ContactPerson[personNumber][4] << endl;

    personNumber = personNumber + 1;
}

void Contact_Management_System :: list_all(){
    cout << "all contact person" << endl;
    cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "address" << endl;
    for(int i=0; i<personNumber; i++){
        cout << ContactPerson[i][0] << "\t" <<ContactPerson[i][1] << "\t" << ContactPerson[i][2] << "\t" << "\t" << ContactPerson[i][3] << "\t" << ContactPerson[i][4] << endl;
    }
}

void Contact_Management_System :: search(){
    string search_name;
    string search_gender;
    cout << "Enter the name of the contact person you want to search: ";
    cin >> search_name;
    cout << "Enter the gender of the contact person you want to search: ";
    cin >> search_gender;

    for (int i = 0; i<personNumber; i++){
        if (ContactPerson[i][1] == search_name && ContactPerson[i][0] == search_gender){ 
            cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "address" << endl;
            cout << ContactPerson[i][0] << "\t" << ContactPerson[i][1] << "\t" << ContactPerson[i][2] << "\t" << "\t" << ContactPerson[i][3] << "\t" << ContactPerson[i][4] << endl;
            cout << "Search completed";
            break;
        } else if (ContactPerson[i][1] != search_name || ContactPerson[i][1] != search_gender){
            if (i == (personNumber-1)){
                cout << "Not found...";
                break;
            }
        }
    }
}

void Contact_Management_System :: edit(){
    string search_edit_name;
    string search_edit_gender;
    string search_new_name;
    string search_new_gender;
    string search_new_phonenumber;
    string search_new_email;
    string search_new_address;
    int edit_option;
    cout << "Enter the name of the contact person you want to edit: ";
    cin >> search_edit_name;
    cout << "Enter the gender of the contact person you want to edit: ";
    cin >> search_edit_gender;

    for (int i=0 ; i < personNumber; i++){
        if (ContactPerson[i][1] == search_edit_name && ContactPerson[i][0] == search_edit_gender){
            cout << "Enter the number you want to edit" << "\t" << "gender: 1, name: 2, phone number: 3, email: 4, address: 5";
            cin >> edit_option;
            switch (edit_option){
                case 1 :
                    cout << "Enter the new gender:";
                    cin >> ContactPerson[i][0];
                    cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "address" << endl;
                    cout << ContactPerson[i][0] << "\t" << ContactPerson[i][1] << "\t" << ContactPerson[i][2] << "\t" << ContactPerson[i][3] << "\t" << ContactPerson[i][4] << "\n";
                    break;
                case 2 :
                    cout << "Enter the new name:";
                    cin >> ContactPerson[i][1];
                    cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "address" << endl;
                    cout << ContactPerson[i][0] << "\t" << ContactPerson[i][1] << "\t" << ContactPerson[i][2] << "\t" << ContactPerson[i][3] << "\t" << ContactPerson[i][4] << "\n";
                    break;                       
                case 3 :
                    cout << "Enter the new phone number:";
                    cin >> ContactPerson[i][2];
                    cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "address" << endl;                            
                    cout << ContactPerson[i][0] << "\t" << ContactPerson[i][1] << "\t" << ContactPerson[i][2] << "\t" << ContactPerson[i][3] << "\t" << ContactPerson[i][4] << "\n";
                    break;
                case 4 :
                    cout << "Enter the new email:";
                    cin >> ContactPerson[i][3];
                    cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "address" << endl;                            
                    cout << ContactPerson[i][0] << "\t" << ContactPerson[i][1] << "\t" << ContactPerson[i][2] << "\t" << ContactPerson[i][3] << "\t" << ContactPerson[i][4] << "\n";
                    break;
                case 5:
                    cout << "Enter the new address:";
                    cin >> ContactPerson[i][4];
                    cout << "gender" << "\t" << "name" << "\t" << "phone number" << "\t" << "email" << "\t" << "address" << endl;                            
                    cout << ContactPerson[i][0] << "\t" << ContactPerson[i][1] << "\t" << ContactPerson[i][2] << "\t" << ContactPerson[i][3] << "\t" << ContactPerson[i][4] << "\n";
                    break;
            }
            break;
        } else if (ContactPerson[i][0] != search_edit_name || ContactPerson[i][1] != search_edit_gender){
            if(i == (personNumber-1)){
                cout << "Not found...";
            }
        }
    }
}

void Contact_Management_System :: delete_contact(){
    string delete_name;
    string delete_gender;
    cout << "Enter the name of the contact person you want to delete: ";
    cin >> delete_name;
    cout << "Enter the gender of the contact person you want to delete: ";
    cin >> delete_gender;

    for (int i = 0; i < personNumber; i++){
        if (ContactPerson[i][1] == delete_name && ContactPerson[i][0] == delete_gender){
            for (int j = i; j < (personNumber-1); j++){
                for (int k; k < 5; k++){
                    ContactPerson[j][k] = ContactPerson[j+1][k];
                }
            }
            personNumber -= 1;
            cout << "Delete completed";
            break;
        } else if(ContactPerson[i][1] != delete_name || ContactPerson[i][0] != delete_gender){
            if (i == (personNumber-1)){
                cout << "Not found...";
                break;
            }             
        }
    }
            
}

void Contact_Management_System :: call_contact(){
    string call_name;
    string call_gender;
    cout << "Enter the name of the contact person you want to call: ";
    cin >> call_name;
    cout << "Enter the gender of the contact person you want to call: ";
    cin >> call_gender;

    for (int i = 0; i < personNumber; i++){
        if (ContactPerson[i][1] == call_name && ContactPerson[i][0] == call_gender){
            cout << "Calling......";
        } else if(ContactPerson[i][1] != call_name || ContactPerson[i][0] != call_gender){
            if (i == (personNumber-1)){
                cout << "Not found...";
                break;
            }
        }
    }
}

// void Contact_Management_System :: output_file(){
//     fstream newFile;
//     newFile.open("contactperson.txt", ios::app);
//     for (int i = 0; i < personNumber; i++){
//         for (int j = 0; j < 5; j = j+1){
//             newFile << ContactPerson[i][j];
//             newFile << " ";
//         }
//         newFile << endl;
//     }
//     newFile.close();
//     cout << "Completed!" << endl;
// }

int main()
{
    Contact_Management_System CMS;
    CMS.userSelect = 0; // 預設使用者選擇的是0
    
    ifstream infile;
    infile.open("contactperson.txt", ios::in);
    for(int i = 0;i < 50 ; i ++){
        for(int j = 0 ; j < 5 ; j++){
            infile >> CMS.ContactPerson[i][j];
        }
        if(CMS.ContactPerson[i][0].length() != 0){
            personNumber += 1;
        }
    }

    while (1){
        // CMS.input_file();
        CMS.showMenu();

        cout << "please enter the number: ";
        cin >> CMS.userSelect;

        switch (CMS.userSelect){
            case 0:{
                ofstream outFile("contactperson.txt");
                for (int i = 0; i < personNumber; i++){
                    for (int j = 0; j < 5; j++){
                    outFile << CMS.ContactPerson[i][j] << " " ;
                    }
                outFile << endl;
                }
                outFile.close();
            
                cout << "byebye";
                
                return 0;
            }
            case 1:
                CMS.add();
                break;

            case 2:
                CMS.list_all();
                break;

            case 3:
                CMS.search();
                break;

            case 4:
                CMS.edit();
                break;

            case 5:
                CMS.delete_contact();
                break;

            case 6:
                CMS.call_contact();
                break;
        }
    }
    
}
