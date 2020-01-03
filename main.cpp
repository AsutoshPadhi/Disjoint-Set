#include <iostream>

using namespace std;

struct node
{
    int key;
    int rank;
    struct node* parent;
};

struct codebook
{
    struct node* element;
    int status;
};

struct node* Make_Set(int n)
{
    struct node* t = (struct node*) malloc (sizeof(struct node));
    t->key = n;
    t->rank = 0;
    t->parent = t;

    return t;
}

struct node* Find_Set(struct node* x)
{
    if(x == NULL)
        return NULL;

    if(x != x->parent)
    {
        x->parent = Find_Set(x->parent);
    }

    return x->parent;
}

struct node* Union(struct node* a, struct node* b)
{
    if(a == NULL)
        return b;

    struct node* x = Find_Set(a);
    struct node* y = Find_Set(b);

    if(x->rank > y->rank)
    {
        y->parent = x;
        return x;
    }
    else if(x->rank < y->rank)
    {
        x->parent = y;
        return y;
    }
    else
    {
        y->parent = x;
        x->rank++;
        return x;
    }
}

int Find(struct codebook* arr[], int n, int key)
{
    for(int i=0; i<n; i++)
    {
        if(arr[i]->element != NULL && arr[i]->element->key == key)
            return i;
    }
}

void Find_Extract_Min(int m, int n, int e[], struct codebook* K[], struct node* address[])
{
    for(int i=0; i<9; i++)
    {
        struct node* parent = Find_Set(address[i]);
        int j = Find(K, n, parent->key);
        cout<<"---------------------------------------------------------------------"<<endl;
        cout<<"i = "<<i+1<<" j = "<<j<<" parent = "<<parent->key<<endl;

        if(j < m)
        {
            e[j] = i+1;
            for(int l=j+1; l<n; l++)
            {
                if(K[l]->status == 0)
                {
                    K[j]->status = 1;
                    cout<<"l = "<<l<<endl;
                    if(K[l]->element == NULL)
                    {
                        K[l]->element = K[j]->element;
                        K[l]->status = 0;
                    }
                    else
                    {
                        struct node* p = Union(K[j]->element, K[l]->element);
                        K[l]->element = p;
                    }

                    K[j]->element = NULL;

                    for(int k=0; k<n; k++)
                    {
                        if(K[k]->element != NULL)
                            cout<<"k = "<<k<<" -> "<<K[k]->element->key;
                        else
                            cout<<"k = "<<k<<" -> NULL";
                        cout<<"\tstatus = "<<K[k]->status<<endl;
                    }
                    break;
                }

            }
        }
        for(int k=0; k<m; k++)
        {
            cout<<e[k]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    struct node* address[9];
    for(int i=0; i<9; i++)
        address[i] = NULL;
    
    for(int i=0; i<9; i++)
    {
        address[i] = Make_Set(i+1);
    }
    int n;
    int m;
    
    cin>>m>>n;
    int e[m] = {0};
    struct codebook* arr[n];
    for(int i=0; i<n; i++)
    {
        arr[i] = (struct codebook*) malloc(sizeof(struct codebook));
        arr[i]->element = NULL;
        arr[i]->status = 0;
    }

    struct node* x = NULL;
    struct node* y = NULL;
    int index = 0;
    char ip;
    int ct=0;
    // cout<<"check1"<<endl;
    while(cin>>ip)
    {

        if(ip != 'E')
        {
            y = address[(int)(ip-'0') - 1];
            cout<<"\t"<<(int)(ip-'0')<<" root = ";
            struct node* x_root = Find_Set(x);
            struct node* y_root = Find_Set(y);
            x = Union(x_root, y_root);
            cout<<x->key<<endl;
        }
        else
        {
            arr[index]->element = x;
            // cout<<"\t"<<x->key<<endl;
            index++;
            x = NULL;
        }
    }

    for(int i=0; i<n; i++)
    {
        if(arr[i]->element != NULL)
            cout<<arr[i]->element->key<<endl;
        else
            cout<<"NULL"<<endl;
    }

    for(int i=0; i<9; i++)
    {
        cout<<"i = "<<i+1<<" parent = "<<Find_Set(address[i])->key<<endl;
    }

    Find_Extract_Min(m, n, e, arr, address);

    for(int i=0; i<m; i++)
    {
        cout<<e[i]<<" ";
    }
    cout<<endl;

    cout<<"Completed"<<endl;
    return 0;
}