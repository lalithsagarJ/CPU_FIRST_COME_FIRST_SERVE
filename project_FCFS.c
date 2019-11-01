#include<stdio.h>
#include<stdlib.h>

struct node{
	int no;
	float at,bt,pc,tat,wt,rt,rd;
	struct node *link;
};

typedef struct node *NODE;

void create_node(NODE *p,int no,float at,float bt,float *fr){
	
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
	printf("\t");
	for(i=1;i<=process;i++){
		printf("%.1f      \t",r->pc);
		r=r->link;
	}
}

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
		printf("\nResponse Time: %.2f\n",p->rt);
		
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
	NODE start=NULL;
	int process,i;
	float arrival_time,brust_time,first_response;
	printf("Enter the number of Processes :");
	scanf("%d",&process);
	for(i=1;i<=process;i++){
		printf("\nEnter the Details for Process %d:\n",i);
		printf("\tArrival Time: ");
		scanf("%f",&arrival_time);
		printf("\tBrust Time: ");
		scanf("%f",&brust_time);
		if(i==1)
			first_response=arrival_time;
		create_node(&start,i,arrival_time,brust_time,&first_response);
	}
	
	printf("\n<------------------------------------------------ START ------------------------------------------------>\n");
	process_chart(start,process);
	display(start,process);
	printf("\n<------------------------------------------------ END -------------------------------------------------->\n");
	return 0;
}
