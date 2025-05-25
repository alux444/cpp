#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
    private:
        string name;
        int age;
    public:
        Person(): name(""), age(0) {};
        
        string getName() const { return name; }
        void setName(string n) { name = n; }
        int getAge() const { return age; }
        void setAge(int a) { age = a; }
        
        virtual void getdata() { cin >> this->name >> this->age; }
        virtual void putdata() { cout << this->name << " " << this->age << endl; }
};

class Professor : public Person {
    private:
        static int nextId;
        int publications;
        int cur_id;
    public:
        Professor() : Person(), publications(0), cur_id(nextId++) {}
        void getdata() {
            string fetchedName;
            int fetchedAge;
            cin >> fetchedName >> fetchedAge >> this->publications;
            setName(fetchedName);
            setAge(fetchedAge);
        }
        void putdata() {
            cout << getName() << " "
                << getAge() << " " 
                << publications << " " 
                << cur_id << endl;
        }
};

#define NUM_OF_MARKS 6
class Student : public Person {
    private:
        static int nextId;
        int marks[NUM_OF_MARKS];
        int cur_id;
    public:
        Student(): Person(), cur_id(nextId++) {}
        void getdata() {
            string fetchedName;
            int fetchedAge;
            cin >> fetchedName >> fetchedAge;
            setName(fetchedName);
            setAge(fetchedAge);
            
            for (int i=0; i<NUM_OF_MARKS; i++) {
                cin >> marks[i];
            }
        }
        void putdata() {
            int marksSum {0};
            for (int& mark : marks) {
                marksSum+=mark;
            }
            cout << getName() << " "
                << getAge() << " " 
                << marksSum << " "
                << cur_id << endl;
        }
};

// initialising nextIds at 1
int Professor::nextId = 1;
int Student::nextId = 1;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
