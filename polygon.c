#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#define n 100
struct polygon
{
	int s,hval,vval;
};
struct line
{
	int startx,endx,starty,endy;
};
int main()
{
	struct polygon a[n][n];
	struct line hor[n*n],ver[n*n];
	srand(time(NULL));
	FILE *f=fopen("poly.txt","w");
	if(f==NULL)
	{
		printf("could not open file.\n");
		exit(1);
	}
	int i,j,k,p=0,row,col,time,startr,startc,rowval,colval,x,y,x1,y1,x2,y2,count=0,h,v,q;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j].s=0;
		}
	}
	time=rand()%((n-1)*(n-1)+1);
	//printf("time=%d\n",time);
	for(i=1;i<=time;i++)
	a[rand()%(n-1)][rand()%(n-1)].s=1;
	for(i=0;i<n;i++)
	{
	row=0;
	col=0;
	for(j=0;j<n;j++)
	{
		if(a[i][j].s==1)
		{
			count++;
			if(count==1)
			{
				startr=i;
				startc=j;
			}
			row++;
		}
		if(a[j][i].s==1)
			col++;
	}

	if(row%2!=0)
	{
		a[i][n-1].s=1;
	}
	if(col%2!=0)
	{
		a[n-1][i].s=1;}
	}
	for(i=0;i<n;i++)
	{
	colval=1;
		for(j=0;j<n;j++)
		{
			if(a[j][i].s==1)
				a[j][i].vval=colval++;
		}
			
	}
	for(i=0;i<n;i++)
	{
		rowval=1;
		for(j=0;j<n;j++)
		{
		if(a[i][j].s==1)
			a[i][j].hval=rowval++;
		}
	}

	/*for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
	if(a[i][j].s==1)
	printf(".\t");
	else printf("\t");
	}
	printf("\n");
	}

	for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
	if(a[i][j].s==1)
	printf("%d,%d\t",a[i][j].hval,a[i][j].vval);
	else printf("\t");
	}
	printf("\n");
	}*/
	count=0;
	x=startc;
	y=startr;

	fprintf(f,"%d\t%d\n",startc,startr);

	do
	{
	h=a[y][x].hval;
	v=a[y][x].vval;
	count=1-count;
	if(count==1)//move horizontally
	{
		if(h%2==0)
		{
			for(i=x-1;i>=0;i--)
			{
			if(a[y][i].s==1)
			{
			x=i;
			break;
			}
			}
		}
		else
		{
			for(i=x+1;i<n;i++)
			{
			if(a[y][i].s==1)
			{
			x=i;
			break;
			}
			}
		}
	}
	if(count==0)//move vertically
	{
		if(v%2==0)
		{
			for(i=y-1;i>=0;i--)
			{
			if(a[i][x].s==1)
			{
			y=i;
			break;
			}
			}
		}
		else
		{
			for(i=y+1;i<n;i++)
			{
			if(a[i][x].s==1)
			{
			y=i;
			break;
			}
			}
		}
	}
	fprintf(f,"%d\t%d\n",x,y);
	}while(x!=startc || y!=startr);
	fclose(f);
	f=fopen("poly.txt","r");
	count=0;
	i=0;
	j=0;
	fscanf(f,"%d\t%d",&x1,&y1);
	while(!feof(f))
	{
		fscanf(f,"%d\t%d",&x2,&y2);
		if(count==0)
		{
			hor[i].startx=x1;
			hor[i].endx=x2;
			hor[i].starty=y1;
			hor[i++].endy=y2;
		}
		else
		{
			ver[j].startx=x1;
			ver[j].endx=x2;
			ver[j].starty=y1;
			ver[j++].endy=y2;
		}
		//printf("%d\t%d\t\t%d\t%d\n",x1,y1,x2,y2);
		x1=x2;
		y1=y2;
		count=1-count;
	}
	fclose(f);
	f=fopen("intersection","w");
	count=0;
	for(p=0;p<j;p++)
	{
		for(q=0;q<i;q++)
		{//printf("p=%d q=%d count=%d\n",p,q,count);
			x=ver[p].startx;
			y=hor[q].starty;
			x1=hor[q].startx;
			x2=hor[q].endx;
			y1=ver[p].starty;
			y2=ver[p].endy;
			if(((x1>x && x2<x)||(x1<x && x2>x)) && ((y1>y && y2<y)||(y1<y && y2>y)))
			{//count++;
				fprintf(f,"%d\t%d\n",x,y);
			}
		}
	}
return 0;
}




















