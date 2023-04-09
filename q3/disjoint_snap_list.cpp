#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

//taken from dataset website
const unsigned long int num_vertex = 81306; //vertex numbering goes from 0 to 4038
const unsigned long int num_edges = 1768149; //umber of lines in dataset, will be inly used to display progress bar

const char file_path[] = "C:\\Users\\Ananya\\Downloads\\twitter.tar.gz";

struct node;

struct CC
{
    CC *next;
    CC *prev;
    node *head;
    node *tail;
    unsigned long int len;
};

struct node
{
    CC *rep;
    unsigned long int data;
    node *next;
};

struct edge
{
    unsigned long int value1;
    unsigned long int value2;
};

//this function initiates all the num_vertex nodes to a default value
void MAKE_SET(unsigned long int x, CC *start) //x is the index
{
    CC *temp = start->next;

    CC *new_CC = new CC;
    new_CC->len = 1;
    new_CC->next = temp;
    start->next = new_CC;
    new_CC->prev = start;

    if (temp != NULL)
        temp->prev = new_CC;

    new_CC->head = new node;
    new_CC->tail = new_CC->head;
    new_CC->head->data = x;
    new_CC->head->rep = new_CC;
    new_CC->head->next = NULL;
}

CC *FIND_SET(unsigned long int val, CC *start)
{
    CC *CC_iterator = start->next;

    while (CC_iterator != NULL)
    {
        node *node_iterator = CC_iterator->head;

        while (node_iterator != NULL)
        {
            if (node_iterator->data == val)
                return node_iterator->rep;

            node_iterator = node_iterator->next;
        }
        CC_iterator = CC_iterator->next;
    }
    return NULL;
}

void LINK(CC *x, CC *y)
{
    if (x != y)
    {
        CC *max, *min;

        if (x->len > y->len)
        {
            max = x;
            min = y;
        }
        else
        {
            max = y;
            min = x;
        }

        max->len += min->len;

        node *changin_pt = min->head;

        max->tail->next = min->head;
        max->tail = min->head;

        while (changin_pt != NULL)
        {
            changin_pt->rep = max;
            changin_pt = changin_pt->next;
        }

        if (min->prev != NULL)
            min->prev->next = min->next;

        if (min->next != NULL)
            min->next->prev = min->prev;

        delete min;
    }
}

void UNION(edge temp, CC *start)
{
    if (temp.value1 != temp.value2)
        LINK(FIND_SET(temp.value1, start), FIND_SET(temp.value2, start));
}

void update_edge(edge &given_edge, ifstream &fin)
{
    if (!fin.eof())
    {
        char line[10];
        fin.getline(line, 10);

        stringstream str_strm;
        str_strm << line; //convert the string s into stringstream

        char num[5];

        str_strm >> num;
        given_edge.value1 = atoi(num);

        str_strm >> num;
        given_edge.value2 = atoi(num);

        // cout << given_edge.value1 << " " << given_edge.value2 << endl;
    }
}

const int num_iter = 1;

int main()
{
    float avg_time = 0;

    for (int master = 0; master < num_iter; master++)
    {
        float start_time = clock();

        CC *start = new CC;
        start->head = NULL;
        start->tail = NULL;
        start->len = 0;
        start->next = NULL;
        start->prev = NULL;

        for (int i = 0; i < num_vertex; i++)
            MAKE_SET(i, start);

        ifstream fin(file_path, ios::in);

        edge temp;
        for (int i = 0; i < num_edges; i++)
        {
            update_edge(temp, fin);
            UNION(temp,start);

            cout << (float)i / (num_edges - 1) * 100 << "% done \r";
        }

        fin.close();

        float end_time = clock();

        float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
        avg_time += time_taken;
        cout << "Time Taken: " << time_taken << "ms" << endl;
    }

    avg_time /= num_iter;
    cout << "Average Time Taken: " << avg_time << "ms" << endl;

    return 0;
   

}
