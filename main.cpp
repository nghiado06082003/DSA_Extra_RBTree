#include "RedBlackTree.cpp"
#include "AVLTree.cpp"
#include "Student.h"

void skew_bl_test()
{
    RedBlackTree<int> rbTree;
    AVLTree<int> avlTree;
    int test = 5;
    while (test <= 35) {
        rbTree.insert(test);
        avlTree.insert(test);
        test += 5;
    }
    cout << "RedBlackTree: \n";
    rbTree.printInOrder();
    rbTree.printStructure();

    cout << "\n--------------------------------------------------------------------\n";

    cout << "AVLTree: \n";
    avlTree.printInOrder();
    avlTree.printStructure();
}

void skew_bl_test_2()
{
    RedBlackTree<int> rbTree;
    AVLTree<int> avlTree;
    vector<int> test = { 3393,9108,7891,9085,2638,1313,3897,4380,1618,4858 };
    for (auto i : test)
    {
        rbTree.insert(i);
        avlTree.insert(i);
    }
    cout << "RedBlackTree: \n";
    rbTree.printInOrder();
    rbTree.printStructure();

    cout << "\n--------------------------------------------------------------------\n";

    cout << "AVLTree: \n";
    avlTree.printInOrder();
    avlTree.printStructure();
}

void ins_del_test()
{
    RedBlackTree<int> rbTree;
    AVLTree<int> avlTree;
    const int NUM_OF_ELEMENT = 50000;
    vector<int> numList;
    srand(7);
    for (int i = 0; i < NUM_OF_ELEMENT; i++)
        numList.push_back(rand());
    cout << "Red-Black Tree: \n";
    auto start_1 = high_resolution_clock::now();
    for (int i = 0; i < NUM_OF_ELEMENT; i++)
        rbTree.insert(numList[i]);
    auto stop_1 = high_resolution_clock::now();
    auto duration_1 = duration_cast<microseconds>(stop_1 - start_1);
    cout << "Time taken for red black tree insertion: " << duration_1.count() << " microseconds" << endl;
    cout << "\n--------------------------------------------------------------------\n";
    cout << "AVL Tree: \n";
    auto start_2 = high_resolution_clock::now();
    for (int i = 0; i < NUM_OF_ELEMENT; i++)
        avlTree.insert(numList[i]);
    auto stop_2 = high_resolution_clock::now();
    auto duration_2 = duration_cast<microseconds>(stop_2 - start_2);
    cout << "Time taken for AVL tree insertion: " << duration_2.count() << " microseconds" << endl;
    cout << "\n--------------------------------------------------------------------\n";
    auto start_3 = high_resolution_clock::now();
    bool temp_1_rb = rbTree.isContain(numList[13579]);
    bool temp_2_rb = rbTree.isContain(-1);
    auto stop_3 = high_resolution_clock::now();
    auto duration_3 = duration_cast<microseconds>(stop_3 - start_3);
    cout << "Time taken to find in red black tree: " << duration_3.count() << " microseconds" << endl;
    cout << numList[13579] << ( temp_1_rb ? ": Found" : ": Not found" ) << endl;
    cout << -1 << ( temp_2_rb ? ": Found" : ": Not found" ) << endl;
    cout << "\n--------------------------------------------------------------------\n";
    auto start_4 = high_resolution_clock::now();
    bool temp_1_avl = avlTree.isContain(numList[13579]);
    bool temp_2_avl= avlTree.isContain(-1);
    auto stop_4 = high_resolution_clock::now();
    auto duration_4 = duration_cast<microseconds>(stop_4 - start_4);
    cout << "Time taken to find in avl tree: " << duration_4.count() << " microseconds" << endl;
    cout << numList[13579] << (temp_1_avl ? ": Found" : ": Not found") << endl;
    cout << -1 << (temp_2_avl ? ": Found" : ": Not found") << endl;
    cout << "\n--------------------------------------------------------------------\n";
    cout << "Red-Black Tree: \n";
    auto start_5 = high_resolution_clock::now();
    for (int i = 0; i < NUM_OF_ELEMENT; i++)
    {
        rbTree.remove(numList[i]);
        i += 40;
    }
    auto stop_5 = high_resolution_clock::now();
    auto duration_5 = duration_cast<microseconds>(stop_5 - start_5);
    cout << "Time taken for red black tree removement: " << duration_5.count() << " microseconds" << endl;
    cout << "\n--------------------------------------------------------------------\n";
    cout << "AVL Tree: \n";
    auto start_6 = high_resolution_clock::now();
    for (int i = 0; i < NUM_OF_ELEMENT; i++)
    {
        avlTree.remove(numList[i]);
        i += 40;
    }
    auto stop_6 = high_resolution_clock::now();
    auto duration_6 = duration_cast<microseconds>(stop_6 - start_6);
    cout << "Time taken for AVL tree removement: " << duration_6.count() << " microseconds" << endl;
}

void data_test()
{
    RedBlackTree<Student> test;
    ifstream input("D:/DSA_Extra/K21_DTBTL.csv");
    if (!input.is_open()) {
        cout << "Cannot read data. Please recheck.\n";
        return;
    }
    else {
        string line;
        getline(input, line);
        auto start = high_resolution_clock::now();
        while (getline(input, line))
        {
            while (line.find(' ') != string::npos) {
                int pos = line.find(' ');
                line[pos] = '_';
            }
            while (line.find(',') != string::npos) {
                int pos = line.find(',');
                line[pos] = ' ';
            }
            stringstream data(line);
            string dump;
            Student s;
            data >> s.ID >> s.firstName >> s.lastName
                >> s.classID >> s.ProfesAvgTen >> s.ProfesAvgFour
                >> s.ProfesCreditNum >> s.passedSubject
                >> dump >> dump >> dump >> dump >> dump >> dump >> dump
                >> s.generalAvgTen >> s.generalAvgFour >> s.generalCreditNum;
            test.insert(s);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken for reading and inserting data into tree: " << duration.count() << " microseconds" << endl;
        cout << "Data is successfully read.\n";
    }
    int option = 0;
    do {
        cout << "Please choose one option below:" << endl;
        cout << "=================================================================" << endl;
        cout << "0)\t" << "End program." << endl
            << "1)\t" << "Print information of all students." << endl
            << "2)\t" << "Print information of student with ID type in by user." << endl
            << "3)\t" << "Add a new students into the data." << endl
            << "4)\t" << "Remove one student out of the data." << endl;
        cout << "=================================================================" << endl;
        cout << "Type in your option: ";
        cin >> option;
        switch (option) {
            case 0:
            {
                cout << "Thank you for using this function!" << endl;
                break;
            }
            case 1:
            {
                auto start = high_resolution_clock::now();
                test.printList();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken for print ~ time taken for traversing all node in the tree (and print them): " << duration.count() << " microseconds" << endl;
                break;
            }
            case 2:
            {
                int IDnum = -1;
                cout << "Please type in the ID of student: ";
                cin >> IDnum;
                auto start = high_resolution_clock::now();
                if (!test.isValidKey(IDnum))
                {
                    auto stop = high_resolution_clock::now();
                    cout << "ID is not in the data\n";
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "Time taken for valid check (find node once): " << duration.count() << " microseconds" << endl;
                    break;
                }
                else
                {
                    cout << test.get(IDnum);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "Time taken for valid check & get (find node twice and print): " << duration.count() << " microseconds" << endl;
                    break;
                }
            }
            case 3:
            {
                Student s;
                cout << "Please type in the student's information (seperate each element with a space, end with enter): ";
                cin >> s.ID >> s.firstName >> s.lastName
                    >> s.classID >> s.ProfesAvgTen >> s.ProfesAvgFour
                    >> s.ProfesCreditNum >> s.passedSubject
                    >> s.generalAvgTen >> s.generalAvgFour >> s.generalCreditNum;
                auto start = high_resolution_clock::now();
                test.insert(s);
                auto stop = high_resolution_clock::now();
                cout << "You has just insert into the data these information: \n";
                cout << s;
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken for inserting: " << duration.count() << " microseconds" << endl;
                break;
            }
            case 4:
            {
                int IDnum = -1;
                cout << "Please type in the ID of student: ";
                cin >> IDnum;
                auto start = high_resolution_clock::now();
                if (!test.isValidKey(IDnum))
                {
                    auto stop = high_resolution_clock::now();
                    cout << "ID is not in the data\n";
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "Time taken for valid check (find node once): " << duration.count() << " microseconds" << endl;
                    break;
                }
                else
                {
                    test.remove(test.get(IDnum));
                    auto stop = high_resolution_clock::now();
                    cout << "Successfully removed!\n";
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "Time taken for valid check & remove (find node and remove process): " << duration.count() << " microseconds" << endl;
                    break;
                }
            }
            default:
            {
                cout << "Option is not valid. Please type in again next time, or type in 0 if you want to end program!\n";
            }
        }
    } while (option != 0);
}

bool findPairs(int* arr, int n, pair<int, int>& pair1, pair<int, int>& pair2)
{
    struct sumPair {
        int sum;
        pair<int, int> index;
        sumPair() { sum = -1; index = make_pair(-1, -1); }
        sumPair(int sum, const pair<int, int>& index) { this->sum = sum; this->index = index; }
        sumPair(const sumPair& other) { this->sum = other.sum; this->index = other.index; }
        void operator = (const sumPair& other) { this->sum = other.sum; this->index = other.index; }
        bool operator < (const sumPair& other) { return (this->sum < other.sum); }
        bool operator > (const sumPair& other) { return (this->sum > other.sum); }
        bool operator == (const sumPair& other) { return (this->sum == other.sum); }
        bool operator < (int sum) { return (this->sum < sum); }
        bool operator > (int sum) { return (this->sum > sum); }
        bool operator == (int sum) { return (this->sum == sum); }
    };
    RedBlackTree<sumPair> map;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int sum = arr[i] + arr[j];
            if (!map.isValidKey(sum))
            {
                sumPair temp(sum, make_pair(i, j));
                map.insert(temp);
            }
            else
            {
                int index1 = map.get(sum).index.first;
                int index2 = map.get(sum).index.second;
                if (index1 != i && index1 != j && index2 != i && index2 != j)
                {
                    pair1.first = arr[index1];
                    pair1.second = arr[index2];
                    pair2 = make_pair(arr[i], arr[j]);
                    return true;
                }
            }
        }
    }
    return false;
}

void findPairs1()
{
    int arr[] = { 3, 4, 7, 1, 2, 9, 8 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) {
        cout << "First pair: " << pair1.first << " - " << pair1.second << endl
            << "Second pair: " << pair2.first << " - " << pair2.second << endl;
    }
    else
        cout << "No pair found." << endl;
}
void findPairs2()
{
    srand(29);
    int* arr = new int[100000];
    for (int i = 0; i < 100000; i++)
        arr[i] = rand();
    pair<int, int> pair1, pair2;
    auto start = high_resolution_clock::now();
    bool check = findPairs(arr, 100000, pair1, pair2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken for running findPairs function: " << duration.count() << " microseconds" << endl;
    if (check) {
        cout << "First pair: " << pair1.first << " - " << pair1.second << endl
            << "Second pair: " << pair2.first << " - " << pair2.second << endl;
    }
    else
        cout << "No pair found." << endl;
    delete[] arr;
}
void findPairs3()
{
    int arr[] = { 65, 30, 7, 90, 1, 9, 8 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) {
        cout << "First pair: " << pair1.first << " - " << pair1.second << endl
            << "Second pair: " << pair2.first << " - " << pair2.second << endl;
    }
    else
        cout << "No pair found." << endl;
}

int main()
{
    findPairs2();
    return 0;
}

