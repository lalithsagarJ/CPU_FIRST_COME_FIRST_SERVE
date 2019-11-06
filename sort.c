/*program to schedule cpu processes according to user choice*/
//using linked list to do every process
#include<stdio.h>
#include<stdlib.h>

struct node{
	int no;
	float at,bt,pc,tat,wt,rt,rd,prt;
	struct node *link;
};

typedef struct node* NODE;
NODE start=NULL,START=NULL,tstart=NULL;

//creating processes
void create_node(NODE *p,int no,float at,float bt,float *fr,int prt){
	
	NODE q,r=*p;
	q=(NODE)malloc(sizeof(struct node));
	q->no=no;
	q->at=at;
	q->bt=bt;
	q->rt=*fr-at;
	q->pc=*fr+bt;
	q->tat=q->pc-at;
	q->wt=q->tat-bt;
	q->rd=q->tat/bt;
	q->prt=prt;
	*fr=*fr+bt;
	
	q->link=NULL;
	if(*p==NULL)
		*p=q;
	else{
		while(r->link!=NULL)
			r=r->link;
		r->link=q;
	}
}


 //Gnatt chart for processes
void process_chart(NODE p,int process){
	int i;
	NODE r=p;
	printf("arrival time is : %.1f",r->at);
	printf("\n\nProcess chart:\n");
	for(i=1;i<=process;i++)
		printf("----------------");
	printf("\n");

	for(i=1;i<=process;i++){
		printf("|\tP%d\t",p->no);
		p=p->link;
	}
	printf("|\n");
	
	for(i=1;i<=process;i++)
		printf("----------------");
	
	printf("\n");
	printf("%.1f      \t",r->at);
	for(i=1;i<=process;i++){
		printf("%.1f      \t",r->pc);
		r=r->link;
	}
}


//coping main list into another list for sorting
void copy(){
	NODE ptr=start;

	while(ptr!=NULL){
		NODE p=(NODE)malloc(sizeof(struct node));
		
		p->no=ptr->no;
		p->at=ptr->at;
		p->bt=ptr->bt;
		p->pc=ptr->pc;
		p->tat=ptr->tat;
		p->wt=ptr->wt;
		p->rt=ptr->rt;
		p->rd=ptr->rd;
		p->prt=ptr->prt;
		p->link=START;
		START=p;

		ptr=ptr->link;
	}
}


/*                sorting               */    
NODE sortedmerge(NODE a,NODE b){
	NODE result=NULL;
	if(a==NULL)
		return b;
	else if(b==NULL)
		return a;
	if(a->bt <= b->bt){
		result=a;
		result->link=sortedmerge(a->link,b);
	}
	else{
		result=b;
		result->link=sortedmerge(a,b->link);
	}
	return result;
}
void split(NODE temp,NODE *front,NODE *back){
	NODE fast=temp->link;
	NODE slow=temp;
		
	while(fast!=NULL){
		fast=fast->link;
		if(fast!=NULL){
			slow=slow->link;
			fast=fast->link;
		}
	}
	*front=temp;
	*back=slow->link;
	slow->link=NULL;
}
void mergesort(NODE temp){
	NODE ptr=temp,a,b;
	if(temp == NULL || temp->link==NULL)
		return;

	split(ptr,&a,&b);
	mergesort(a);
	mergesort(b);
	temp=sortedmerge(a,b);
}
void dis(){                                     /* ONLY FOR TESTING PURPOSSSE*/
	NODE ptr=START;                             
	while(ptr!=NULL){
		printf("%.1f ",ptr->bt);
		printf("%.1f",ptr->at);
		ptr=ptr->link;
		printf("\n");
	}
}                                               /* ONLY FOR TESTING PURPOSSSE*/


/* display the processes*/					
void display(NODE p,int process){
	float ttat,twt,trd,trt,tbt;
	ttat=twt=trd=trt=tbt=0;
	printf("\n\nProcess Details :");
	while(p!=NULL){
		printf("\n****Process %d****: \n",p->no);
		printf("Arrival time: %.2f\n",p->at);
		printf("Brust Time : %.2f\n",p->bt);
		printf("Turn around time: %.2f\n",p->tat);
		printf("Waiting Time: %.2f\n",p->wt);
		printf("Relative Delay: %.2f\n",p->rd);
		printf("Response Time: %.2f\n",p->rt);
		
		ttat+=p->tat;
		twt+=p->wt;
		trd+=p->rd;
		trt+=p->rt;
		tbt+=p->bt;
		
		p=p->link;
	}
	printf("\n\nOverall Details:\n");
	printf(" Throughput: %.2f\n",process/tbt);
	printf(" Average Turn Around Time: %.2f\n",ttat/process);
	printf(" Average Waiting Time: %.2f\n",twt/process);
	printf(" Average Relative Delay: %.2f\n",trd/process);
	printf(" Average Relative Time: %.2f\n",trt/process);
}

int main(){
	
	int process,i,ch,prt;
	float arrival_time,brust_time,first_response;
	printf("Enter the number of Processes :");
	scanf("%d",&process);
	for(i=1;i<=process;i++){
		printf("\nEnter the Details for Process %d:\n",i);
		printf("\tArrival Time: ");
		scanf("%f",&arrival_time);
		printf("\tBrust Time: ");
		scanf("%f",&brust_time);
		printf("\tPriority: ");
		scanf("%d",&prt);
		if(i==1)
			first_response=arrival_time;
		create_node(&start,i,arrival_time,brust_time,&first_response,prt);
	}
	do
	{
		printf("\n\n------Options For Scheduling------\n1.first come first serve(FCFS)\n2.priority scheduling(preemptive)\n3.shortest job first(preemptive)\n0.exit\n");
		scanf("%d",&ch);
		
		printf("\n<------------------------------------------------ START ------------------------------------------------>\n");
		switch(ch){
			case 1:printf("\nFCFS scheduling\n");
				process_chart(start,process);
				display(start,process);
				break;
			case 2:printf("\npriority scheduling\n");
				break;
			case 3:printf("\nSJF scheduling\n");
				copy();
				mergesort(START);
				dis();   //TESTING
				break;
			default:printf("\nEnter the correct choice\n");
				break;
		}
		printf("\n<------------------------------------------------ END -------------------------------------------------->\n");
	}while(ch!=0);
	return 0;
}
