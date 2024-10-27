#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>
#include <fstream>

using namespace std;

struct Category{

    //This vector stores Category expense
    vector<int> Catexpense;

    //This map stores suncategories and their expenses
    //The key string is the name of the subcategory and the vector stores each expenses that user adds
    map<string , vector<int> > subCatExp;

};

//In this map key string is the name of category and the Category struct stores subcategory and expenses
map<string , Category> Categories ;

void AddCategory(vector<string> &inputLine){

    //inputLine[1] is Category name
    Categories[inputLine[1]]=Category();
    if(inputLine.size()>2){
        for(int i=2 ; i < inputLine.size() ; i++){
            //inputline[i] are subcategories name
            Categories[inputLine[1]].subCatExp[inputLine[i]]= vector<int>() ;
        }
    }
}

void AddExpense(vector<string> &inputLine){

    //changing the string type to int to store in expense vector
    int expense = stoi(inputLine[2]);
    if(inputLine[1].find('/') == string::npos){
        Categories[inputLine[1]].Catexpense.push_back(expense);
    }
    else{
        //spliting the Category name and subcategory name from inputLine[1]
        string categoryName = inputLine[1].substr(0,inputLine[1].find('/'));
        string subCategoryName = inputLine[1].substr((inputLine[1].find('/')+1),inputLine[1].length());

        Categories[categoryName].subCatExp[subCategoryName].push_back(expense);

    }
}

void RemoveExpense(vector<string> &inputLine){

    if(inputLine[1].find('/') == string::npos){
            //erase the last expense added to category
            Categories[inputLine[1]].Catexpense.erase(prev(Categories[inputLine[1]].Catexpense.end()));
        }
        else{
            //spliting the Category name and subcategory name from inputLine[1]
            string categoryName = inputLine[1].substr(0,inputLine[1].find('/'));
            string subCategoryName = inputLine[1].substr((inputLine[1].find('/')+1),inputLine[1].length());

            Categories[categoryName].subCatExp[subCategoryName].erase(prev(Categories[categoryName].subCatExp[subCategoryName].end()));

        }
}

void Report(vector<string> &inputLine){
   
    if(inputLine.size() == 2){
        int threshold = stoi(inputLine[1]);
        for(map<string, Category >::iterator it = Categories.begin(); it != Categories.end() ; it++){

            vector<pair<string, int>> subCatVec;

            for ( map<string , vector<int> >::iterator it2 = Categories[it->first].subCatExp.begin() ;
                it2 != Categories[it->first].subCatExp.end() ; it2++ ){

                int subCatExpense=0;
                
                for(int i=0 ; i < it2->second.size(); i++ ){

                    subCatExpense += it2->second[i];

                }
                subCatVec.push_back(make_pair(it2->first,subCatExpense));
            }
            int CategoryExpense=0;
            for (int i = 0; i < Categories[it->first].Catexpense.size() ; i++){

                CategoryExpense = CategoryExpense + Categories[it->first].Catexpense[i];
            }
            int totalSubexpense=0;
            for(int i=0 ; i<subCatVec.size();i++){
                totalSubexpense += subCatVec[i].second;
            }

            cout << "Category: "<< it->first << endl;
            cout << "Total expenses: "<< (CategoryExpense + totalSubexpense )<<endl;
            cout << "Subcategories expenses:"<< endl;

            //sort the sub categories by value
            sort(subCatVec.begin(), subCatVec.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
                return a.second > b.second;
            });

            for (vector<pair<string , int>>:: iterator it3 =subCatVec.begin();it3 !=subCatVec.end(); it3++){
                if (it3->second >= threshold){
                    cout <<"    - " << it3->first << ": " << it3->second<< endl;
                }
            }

            if(it == prev(Categories.end())){
                cout << "**********"<< endl;
            }
            else{
                cout << "----------"<< endl;
            }        
        }
    }
    else{
        for(map<string, Category >::iterator it = Categories.begin(); it != Categories.end() ; it++){

            vector<pair<string, int>> subCatVec;

            for ( map<string , vector<int> >::iterator it2 = Categories[it->first].subCatExp.begin() ;
                it2 != Categories[it->first].subCatExp.end() ; it2++ ){

                int subCatExpense=0;
                
                for(int i=0 ; i < it2->second.size(); i++ ){

                    subCatExpense += it2->second[i];

                }
                subCatVec.push_back(make_pair(it2->first,subCatExpense));
            }
            int CategoryExpense=0;
            for (int i = 0; i < Categories[it->first].Catexpense.size() ; i++){

                CategoryExpense = CategoryExpense + Categories[it->first].Catexpense[i];
            }
            int totalSubexpense=0;
            for(int i=0 ; i<subCatVec.size();i++){
                totalSubexpense += subCatVec[i].second;
            }

            cout << "Category: "<< it->first << endl;
            cout << "Total expenses: "<< (CategoryExpense + totalSubexpense )<<endl;
            cout << "Subcategories expenses:"<< endl;

            ////sort the sub categories by value
            sort(subCatVec.begin(), subCatVec.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
                return a.second > b.second;
            });

            for (vector<pair<string , int>>:: iterator it3 =subCatVec.begin();it3 !=subCatVec.end(); it3++){
                    cout <<"    - " << it3->first << ": " << it3->second<< endl;
            }

            if(it == prev(Categories.end())){
                cout << "**********"<< endl;
            }
            else{
                cout << "----------"<< endl;
            }        
        }

    }
}

void HandleInput(string userinput){
    vector<string> inputLine;
    stringstream s(userinput);
    string word;
    string command;
    while(s >> word){
        inputLine.push_back(word);
    }
    command =inputLine[0];
    if(command == "new_category"){
        AddCategory(inputLine);
    }
    else if ((command == "add_expense")){
        AddExpense(inputLine);
    }
    else if(command == "remove_expense"){
        RemoveExpense(inputLine);
    }
    else if(command == "report"){
        Report(inputLine);
    }
    else{
        cout << "This command is not defined!"<<endl;
        cout << "Please try again"<<endl;
    }

}

int main(){

    string userInput;
    //ifstream file ("sample.txt"); //remove comment if you want to take input from "sample.txt"
    while(getline(cin , userInput)){

        HandleInput(userInput);
    
    }

}