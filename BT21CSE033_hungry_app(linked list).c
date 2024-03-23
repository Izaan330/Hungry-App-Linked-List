//Roll number: BT21CSE033

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct restaurant_node_tag
{
    int order_count;             // to count number of orders completed by a restaurant
    char eating_joint_type[100]; // restaurant or pub or cafe
    char area[100];              // address
    struct restaurant_node_tag *next;

} restaurant_node;

typedef struct user_node_tag
{
    int user_id;
    int phone_number;
    char area[100];
    struct user_node_tag *next;

    //food_item_list food_menu;

    int vada_pav; // counter
    int pav_bhaji;

    int idli_sambar; // counter
    int dosa_sambar;

    int pizza; // counter
    int burger;


} user_node;

typedef struct agent_node_tag
{
    int cac;    // current accumulated commision
    char area[100]; // agent_area
    int agent_id;
    char name[50];
    int phone_number;
    bool available;
    struct agent_node_tag *next;
} agent_node;


struct food_item_list
{
    int vada_pav; // counter
    int pav_bhaji;

    int idli_sambar; // counter
    int dosa_sambar;

    int pizza; // counter
    int burger;
} max;

typedef struct order_list_tag
{
    int user_id;
    char agent_area[100];
    int phone_number;
    char eating_joint_type[100];
    char menu[100];

    struct order_list_tag *next;
} order_list;

void print_agent_details(agent_node *a_node)
{
    printf("agent id is %d. \n agent name is %s. \n agent area is %s. \n agent phone number is %d\n", a_node->agent_id, a_node->name, a_node->area, a_node->phone_number);
}

void print_order_details(order_list *o_node)
{
    printf("The customer id is %d. \n The area is %s. \n The agent's phone number is %d. \n The eating joint type is %s.\n Food item chosen from menu is %s. \n ", o_node->user_id, o_node->agent_area, o_node->phone_number, o_node->eating_joint_type, o_node->menu);
}

void Search(char *eating_joint_type, char *area, restaurant_node *r_node)
{
    while (((strcmp(r_node->eating_joint_type, eating_joint_type) != 0 || strcmp(r_node->area, area) != 0)) && r_node->next != NULL)
    {
        r_node = r_node->next;
    }
    if (strcmp(r_node->eating_joint_type, eating_joint_type) == 0 && strcmp(r_node->area, area) == 0)
    {
        printf("The restaurant you are looking out is available. \n The area is %s. \n It is of eating-joint-type %s. \n", r_node->area, r_node->eating_joint_type);
    }
    else
    {
        printf("The restaurant you are looking for is not available");
    }
}

void bubbleSort(int array[], int size)
{

    // loop to access each array element
    for (int step = 0; step < size - 1; ++step)
    {

        // loop to compare array elements
        for (int i = 0; i < size - step - 1; ++i)
        {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (array[i] > array[i + 1])
            {

                // swapping occurs if elements
                // are not in the intended order
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

void assign_agent(char* agent_area,agent_node* a_node,order_list* new_order){
    //     // snippet to assign agent based on availability and area

    while(a_node!=NULL)
    {
        if(strcmp(agent_area,a_node->area)==0 && a_node->available==true)
        {
             a_node->available = false;
                    printf("agent number %d has been assigned to the order\n", a_node->agent_id);
                    printf("agent details are :\n");
                    print_agent_details(a_node);
                    printf("order details are : \n");
                    print_order_details(new_order);
        }
        else if (strcmp(agent_area,a_node->area)==0 && a_node->available==false)
        {
            printf("Agent in that area is busy hence cant be assigned");
        }
        a_node=a_node->next;
    }

    
}

void update_menu(user_node* u_node, order_list* new_order)
{
        while (((u_node->user_id) - (new_order->user_id)) != 0)
    {
        u_node = u_node->next;
    }
    if (strcmp("vada_pav", new_order->menu) == 0)
    {
        u_node->vada_pav++;
        max.vada_pav++;
    }
    else if (strcmp("pav_bhaji", new_order->menu) == 0)
    {
        u_node->pav_bhaji++;
        max.pav_bhaji++;
    }
    else if (strcmp("idli_sambar", new_order->menu) == 0)
    {
        u_node->idli_sambar++;
        max.idli_sambar++;
    }
    else if (strcmp("dosa_sambar", new_order->menu) == 0)
    {
        u_node->dosa_sambar++;
        max.dosa_sambar++;
    }
    else if (strcmp("pizza", new_order->menu) == 0)
    {
        u_node->pizza++;
        max.pizza++;
    }
    else if (strcmp("burger", new_order->menu) == 0)
    {
        u_node->burger++;
        max.burger++;
    }

}


void Order(order_list **head_ref, int customer_id, char *agent_area, int phone_number, char *eating_joint_type, char *menu, agent_node *a_node, user_node *u_node)
{
    order_list* last=*head_ref;
    
    order_list *new_order = (order_list *)malloc(sizeof(order_list));
    new_order->user_id = customer_id;
    strcpy(new_order->agent_area, agent_area);
    new_order->phone_number = phone_number;
    strcpy(new_order->eating_joint_type, eating_joint_type);
    strcpy(new_order->menu, menu);

    new_order->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_order;
        assign_agent(agent_area,a_node,new_order);
        update_menu(u_node,new_order) ;
        return ;
    }
    while (last->next != NULL)
    {
        last = last->next;
    }

     last->next = new_order;
     assign_agent(agent_area,a_node,new_order);
     update_menu(u_node,new_order);

}

   
int print_area_wise_agents(agent_node *a_node, char *agent_area)
{
    int found = 0;
    while ((strcmp(a_node->area, agent_area) != 0) && found == 0)
    {
        while (a_node->next != NULL)
        {
            a_node = a_node->next;
            if (strcmp(a_node->area, agent_area) == 0)
            {
                if (a_node->available == true)
                {
                    found = 1;
                    printf("agent number is %d \n", a_node->agent_id);
                    printf("agent details are :\n");
                    print_agent_details(a_node);
                }
            }
        }
        found = 1;
    }
    return 0;
}

void print_agent_list_details(agent_node *a_node)
{
    while (a_node != NULL)
    {
        printf("agent id is %d. \n agent name is %s. \n agent area is %s. \n agent phone number is %d\n --------------\n", a_node->agent_id, a_node->name, a_node->area, a_node->phone_number);
        a_node = a_node->next;
    }
}

// i am using the single pointer of order_list
void print_order_list_details(order_list *o_node)
{
    while (o_node != NULL)
    {
        printf("The customer id is %d. \n The area is %s. \n The phone number is %d. \n The eating joint type is %s.\n Food item chosen from menu is %s. \n ----------------------- \n", o_node->user_id, o_node->agent_area, o_node->phone_number, o_node->eating_joint_type, o_node->menu);
        o_node = o_node->next;
    }
}

void print_restaurant_details(char *eating_joint_type, char *area, restaurant_node *r_node)
{
    Search(eating_joint_type, area, r_node);
}

void add_user_node(user_node **head_ref, int user_id, int phone_number, char *area)
{
    user_node *new_user = (user_node *)malloc(sizeof(user_node));
    strcpy(new_user->area, area);
    new_user->phone_number = phone_number;
    new_user->user_id = user_id;

    new_user->vada_pav = 0;
    new_user->pav_bhaji=0;
    new_user->burger=0;
    new_user->pizza=0;
    new_user->dosa_sambar=0;
    new_user->idli_sambar=0;

    new_user->next = (*head_ref);
    (*head_ref) = new_user;
}

// i am specifying the cac down
void add_agent_node(agent_node **head_ref, int agent_id, int phone_number, char *area, int cac, char *name)
{
    agent_node *new_agent = (agent_node *)malloc(sizeof(agent_node));
    strcpy(new_agent->area, area);
    new_agent->phone_number = phone_number;
    new_agent->agent_id = agent_id;
    new_agent->cac = cac;
    strcpy(new_agent->name, name);
    new_agent->available = true;

    new_agent->next = (*head_ref);
    (*head_ref) = new_agent;
}


void add_restaurant_node(restaurant_node **head_ref, int order_count, char *eating_joint_type, char *area)
{
    restaurant_node *new_restaurant = (restaurant_node *)malloc(sizeof(restaurant_node));
    strcpy(new_restaurant->area, area);
    strcpy(new_restaurant->eating_joint_type, eating_joint_type);
    new_restaurant->order_count = order_count;

    new_restaurant->next = (*head_ref);
    (*head_ref) = new_restaurant;
}

void Delivery(order_list **head_ref, agent_node *a_node)
{
    order_list *prev = *head_ref;
    *head_ref = prev->next;

    while (strcmp(prev->agent_area, a_node->area) != 0)
    {
        a_node = a_node->next;
    }

    a_node->available = true;
    printf("agent id: %d is now free", a_node->agent_id);
    a_node->cac += 100;

    free(prev);
}

void Cancel_order(order_list **head_ref, agent_node *a_node, int user_id)
{
    order_list *first = *head_ref;
    order_list *prev;

    if (first != NULL && first->user_id == user_id)
    {
        *head_ref = first->next;
        while (strcmp(first->agent_area, a_node->area) != 0)
        {
            a_node = a_node->next;
        }
        a_node->available = true;
        free(first);
        printf("order cancelled. \n");
    }
    else if (first != NULL && first->user_id != user_id)
    {
        while (first != NULL && first->user_id != user_id)
        {
            prev = first;
            first = first->next;
        }

        while (strcmp(first->agent_area, a_node->area) != 0)
        {
            a_node = a_node->next;
        }
        a_node->available = true;

        prev->next = first->next;
        printf("order  cancelled. \n");
        free(first);
    }
   
}

void Find_favourite_food_of_user(int user_id, user_node *u_node)
{
    int arr[6];

    while (((u_node->user_id) - (user_id)) != 0)
    {
        u_node = u_node->next;
    }

    arr[0] = u_node->vada_pav;
    arr[1] = u_node->pav_bhaji;
    arr[2] = u_node->dosa_sambar;
    arr[3] = u_node->idli_sambar;
    arr[4] = u_node->burger;
    arr[5] = u_node->pizza;

    bubbleSort(arr, 6);
    if (arr[5] == u_node->vada_pav)
    {
        printf("the most favourite food is vada pav");
    }
    else if (arr[5] == u_node->pav_bhaji)
    {
        printf("the most favourite food is pav bhaji");
    }
    else if (arr[5] == u_node->idli_sambar)
    {
        printf("the most favourite food is idli sambar");
    }
    else if (arr[5] == u_node->dosa_sambar)
    {
        printf("the most favourite food is dosa sambar");
    }
    else if (arr[5] == u_node->pizza)
    {
        printf("the most favourite food is pizza");
    }
    else if (arr[5] == u_node->vada_pav)
    {
        printf("the most favourite food is burger");
    }

    if (arr[4] == u_node->vada_pav)
    {
        printf("the 2nd most favourite food is vada pav");
    }
    else if (arr[4] == u_node->pav_bhaji)
    {
        printf("the 2nd most favourite food is pav bhaji");
    }
    else if (arr[4] == u_node->idli_sambar)
    {
        printf("the 2nd most favourite food is idli sambar");
    }
    else if (arr[4] == u_node->dosa_sambar)
    {
        printf("the 2nd most favourite food is dosa sambar");
    }
    else if (arr[4] == u_node->pizza)
    {
        printf("the 2nd most favourite food is pizza");
    }
    else if (arr[4] == u_node->vada_pav)
    {
        printf("the 2nd most favourite food is burger");
    }

    if (arr[3] == u_node->vada_pav)
    {
        printf("the 3rd most favourite food is vada pav");
    }
    else if (arr[3] == u_node->pav_bhaji)
    {
        printf("the 3rd most favourite food is pav bhaji");
    }
    else if (arr[3] == u_node->idli_sambar)
    {
        printf("the 3rd most favourite food is idli sambar");
    }
    else if (arr[3] == u_node->dosa_sambar)
    {
        printf("the 3rd most favourite food is dosa sambar");
    }
    else if (arr[3] == u_node->pizza)
    {
        printf("the 3rd most favourite food is pizza");
    }
    else if (arr[3] == u_node->vada_pav)
    {
        printf("the 3rd most favourite food is burger");
    }
}


void Find_favourite_restaurants(restaurant_node *r_node)
{
     int max = r_node->order_count;
    

    char area[50];
    strcpy(area,r_node->area);


    while (r_node->next != NULL)
    {
        r_node = r_node->next;
        if ( max < r_node->order_count)
        {
            strcpy(area, r_node->area);
            max=r_node->order_count;
        }
    }
    
    printf("The most favourite restaurant lies in area: %s", area);
    
    
    
}

void Find_favourite_food_across_restaurant()
{

    int arr[6];

    arr[0] = max.vada_pav;
    arr[1] = max.pav_bhaji;
    arr[2] = max.dosa_sambar;
    arr[3] = max.idli_sambar;
    arr[4] = max.burger;
    arr[5] = max.pizza;

    bubbleSort(arr, 6);
    if (arr[5] == max.vada_pav)
    {
        printf("the most favourite food is vada pav");
    }
    else if (arr[5] == max.pav_bhaji)
    {
        printf("the most favourite food is pav bhaji");
    }
    else if (arr[5] == max.idli_sambar)
    {
        printf("the most favourite food is idli sambar");
    }
    else if (arr[5] == max.dosa_sambar)
    {
        printf("the most favourite food is dosa sambar");
    }
    else if (arr[5] == max.pizza)
    {
        printf("the most favourite food is pizza");
    }
    else if (arr[5] == max.vada_pav)
    {
        printf("the most favourite food is burger");
    }
}

int main()
{
    user_node *head_ref=NULL;
    
    add_user_node(&head_ref, 20000, 738511113, "kannad");
    add_user_node(&head_ref, 10000, 989008880, "rahuri_k");
    add_user_node(&head_ref, 10001, 123456780, "Ongole");
    
    agent_node *agent_head_ref=NULL;
    
    add_agent_node(&agent_head_ref, 45612, 942370072, "medina", 0, "bhupesh");
    add_agent_node(&agent_head_ref, 45613, 942370073, "muth_galli", 0, "Aditya_t");
    add_agent_node(&agent_head_ref, 45614, 942370074, "pune", 0, "dinesh");
    
    restaurant_node *restaurant_head_ref=NULL;
    
    add_restaurant_node(&restaurant_head_ref, 12, "restaurant", "medina");
    add_restaurant_node(&restaurant_head_ref, 110, "cafe", "muth_galli");
    add_restaurant_node(&restaurant_head_ref, 1000, "pub", "pune");

    
//q1    //print_area_wise_agents(agent_head_ref,"medina");
//q2    //print_agent_details(agent_head_ref);
//q3    //Search("restaurant","mecca",restaurant_head_ref);
//q4    //print_restaurant_details("pub","pune",restaurant_head_ref);
   
    order_list* order_head_ref=NULL;

//q5-ordering question answered
    
    //Order(&order_head_ref,10000,"muth_galli",942370073,"cafe","pav_bhaji",agent_head_ref,head_ref);
    //Order(&order_head_ref,10000,"muth_galli",942370073,"cafe","pav_bhaji",agent_head_ref,head_ref);
    //Order(&order_head_ref,10000,"pune",942370074,"pub","vada_pav",agent_head_ref,head_ref);
    // Order(&order_head_ref,20000,"medina",942370072,"restaurant","vada_pav",agent_head_ref,head_ref);
    //print_order_list_details(order_head_ref);
    


//q6-ordering and delivery answered
   
    //Order(&order_head_ref,10000,"muth_galli",942370073,"cafe","vada_pav",agent_head_ref,head_ref);
    //Delivery(&order_head_ref,agent_head_ref);
    


//q7-ordering and cancelling answered
   
    //Order(&order_head_ref,10000,"muth_galli",942370073,"cafe","vada_pav",agent_head_ref,head_ref);
    //print_order_list_details(order_head_ref);
    //Cancel_order(&order_head_ref,agent_head_ref,10000);
    

//q8-favourite food of user
    
    // Order(&order_head_ref,10000,"muth_galli",942370073,"cafe","pav_bhaji",agent_head_ref,head_ref);
    // Order(&order_head_ref,10000,"pune",942370073,"pub","pav_bhaji",agent_head_ref,head_ref);
    // Order(&order_head_ref,10000,"medina",942370073,"restaurant","pav_bhaji",agent_head_ref,head_ref);
    // Order(&order_head_ref,10000,"pune",942370073,"pub","vada_pav",agent_head_ref,head_ref);
    
    // Find_favourite_food_of_user(10000,head_ref);
    

//q9-find favourite restaurants
   // Find_favourite_restaurants(restaurant_head_ref);
    

//q10-find favourite food across restaurant
   
    // Order(&order_head_ref,10000,"muth_galli",942370073,"cafe","vada_pav",agent_head_ref,head_ref);
    // Order(&order_head_ref,10000,"pune",942370073,"pub","vada_pav",agent_head_ref,head_ref);
    // Order(&order_head_ref,10000,"medina",942370073,"restaurant","vada_pav",agent_head_ref,head_ref);
    // Order(&order_head_ref,10000,"pune",942370073,"pub","vada_pav",agent_head_ref,head_ref);
    
    // Find_favourite_food_across_restaurant();
    
    return 0;
}
