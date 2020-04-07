// #include <iostream>
// #include <string>
// #include <fstream>
// #include <vector>
// #include <iomanip>
// #include <sstream>

// using namespace std;

// class Person{
//     public:
//         string name;
//         Person(string name){
//             this->name = name;
//         };
//         virtual int getAge() {};
//         virtual string getName() {};
//         virtual void print() {};
//         virtual void print_1() {};
//         virtual void setName(string name){}
// };

// class Terry: public Person{
//     public:
//         int age;
//         Terry(string name, int age): Person(name){
//             this->age = age;
//         }
//         int getAge() {
//              return this->age;
//         }
//         string getName(){
//             return this->name;
//         }
//         void print(){
//             cout << "\nTest";
//         }
//         void setName(string name){
//             this->name = name;
//         }

//         void print_1(){
//             this->print();
//         }
// };
// vector<string> split(string str, char splitter){
//     vector<string> vec;
//     string temp;
//     for (int i = 0; i < str.length(); i++) {
//         if (str[i] != splitter)
//             temp += str[i];
//         else {
//             if(temp == "") continue;
//             vec.push_back(temp);
//             temp = "";
//         }
//     }
//     vec.push_back(temp);
//     return vec;
// }
// std::string bid(std::string itemName, std::string sellerName, std::string buyerName, float price){
//     string transaction = "04 ";
//     transaction += itemName;

//     for(int i=itemName.size(); i< 20;i++) transaction += " ";
    
//     transaction += sellerName;
//     for(int i = sellerName.size(); i < 16;i++) transaction += " ";

//     transaction += buyerName;
//     for(int i = buyerName.size(); i < 16;i++) transaction += " ";
    
//     std::ostringstream streamObj;
//     streamObj << std::setprecision(2);
//     streamObj << std::fixed;
//     streamObj << price;

//     string priceFormat = streamObj.str();
//     int originalLength = priceFormat.length();
//     for(int i=0;i<6-originalLength;i++){
//         priceFormat = "0"+priceFormat;
//     }
//     transaction += priceFormat;
    
//     return transaction;
// }

// int main(){
//     // Terry t("Terry", 30);
//     // Person* a = &t;
//     // cout << a->getName();
//     // a->print_1();
//     // a->setName(NULL);
//     // ifstream in("test.txt");
//     // string in_string;
//     // while(getline(in, in_string)){
//     //     // in >> in_string;
//     //     // if(in_string=="END") break;
//     //     if(in_string == "END"){
//     //       break;
//     //       in.close();  
//     //     } 
//     //     cout << in_string << endl;
//     // }

//     // string test =  "item_name           reg_user        admin           100 000011";
//     // vector<string> a = split(test, ' ');
//     // for(int i=0; i<a.size();i++){
//     //     cout << a[i] << endl;
//     // }
//     // cout << a[1];

//     // string num = "101.23";
//     // float a = stof(num);
//     // cout << a;
//     // ofstream out("test.txt", ios::app);
//     // out << "Test" << endl;
//     // out <<"Terry"  << endl;
//     // out << "Unyil"  << endl;
//     // float num = 3.14151617;
//     // // Set Fixed -Point Notation
//     // // streamObj3.setprecision(2);
//     // std::ostringstream streamObj3;
//     // streamObj3 << std::setprecision(2);
//     // streamObj3 << std::fixed;
    
//     // // Set precision to 2 digits
//     // // streamObj3 << std::setprecision(2);
    
//     // //Add double to stream
//     // streamObj3 << num;
    
//     // // Get string from output string stream
//     // std::cout <<  streamObj3.str() << std::endl;
//     // string a = "10.00";
//     // a = "0000"+ a;
//     // cout << refund("existing_user", "reg_user", 100.00);
//     cout << bid("item_name", "reg_user", "admin", 11);

// }

