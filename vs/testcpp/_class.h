#pragma once

namespace Cls {
    class Person {
        int age;
        float height;
    public:
        Person(int a) : age(a) {};
        Person(int a, int h) : age(a), height(h) {};
        int getAge();
        float getHeight() { return height; }
    }per1(18), * per2;

    typedef Person* NSPerson;

    int Person::getAge() {
        return age;
    }

    void test() {
        if (!per2) {
            per2 = new Person{ 19 };
        }
        cout << per1.getAge() << endl;
        cout << per2->getAge() << endl;

        //    Person p1(20);
        //    Person p2 = 21;
        //    Person p3 {22};
        //    Person p4 = {23};
        //    cout << p1.getAge() << endl;
        //    cout << p2.getAge() << endl;
        //    cout << p3.getAge() << endl;
        //    cout << p4.getAge() << endl;
        //
        //    Person *p5 = new Person(25);
        //    Person *p6 = new Person{35};
        //    cout << p5->getAge() << endl;
        //    cout << p6->getAge() << endl;

        Person* per = new Person[2]{ {11,110}, {12, 120} };

        cout << per->getAge() << " -> " << per->getHeight() << endl;
        cout << (per + 1)->getAge() << " -> " << (per + 1)->getHeight() << endl;

        cout << per[0].getAge() << ", " << per[0].getHeight() << endl;
        cout << per[1].getAge() << ", " << per[1].getHeight() << endl;

        Person* pers = new Person[2]{ {28,170}, {27, 164} };
        NSPerson* p = &pers;

        cout << p[0]->getAge() << "-> " << p[0]->getHeight() << endl;
        cout << (p[0] + 1)->getAge() << "-> " << (p[0] + 1)->getHeight() << endl;

        cout << p[0][0].getAge() << ", " << p[0][0].getHeight() << endl;
        cout << p[0][1].getAge() << ", " << p[0][1].getHeight() << endl;
    }

}
