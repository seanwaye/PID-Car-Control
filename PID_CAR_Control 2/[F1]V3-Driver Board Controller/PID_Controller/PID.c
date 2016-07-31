// △u(k)=Kp[e(k)-e(k-1)]+Kie(k)+Kd[e(k)-2e(k-1)+e(k-2)]
// △u(k)=Ae(k)-Be(k-1)+Ce(k-2)

typedef struct PID 
{ 
    int SetPoint;        //设定目标 Desired Value 
    double Proportion;   //比例常数 Proportional Const     
    double Integral;     //积分常数 Integral Const     
    double Derivative;   //微分常数 Derivative Const     
    int LastError;       //Error[-1]     
    int PrevError;       //Error[-2] 
} PID; 

#define P_DATA 100 
#define I_DATA 0.6 
#define D_DATA 1 
#define HAVE_NEW_VELOCITY 0X01 

static PID sPID; 
static PID *sptr = &sPID; 

void IncPIDInit(void) 
{ 
    sptr->LastError = 0;      //Error[-1] 
    sptr->PrevError = 0;      //Error[-2] 
    sptr->Proportion = P_DATA; //比例常数Proportional Const 
    sptr->Integral   = I_DATA;   //积分常数Integral Const 
    sptr->Derivative = D_DATA;   //微分常数Derivative Const 
    sptr->SetPoint = 100;        //目标是100 
}

//增量式PID控制设计  
int IncPIDCalc(int NextPoint) 
{ 
    int iError, iIncpid;                 //当前误差  
    iError = sptr->SetPoint - NextPoint; //增量计算     
    iIncpid = sptr->Proportion * iError             //E[k]项               
              - sptr->Integral * sptr->LastError    //E[k－1]项  
              + sptr->Derivative * sptr->PrevError; //E[k－2]项  

    sptr->PrevError = sptr->LastError;   //存储前一次误差，用于下次计算  
    sptr->LastError = iError; 
    return(iIncpid);                     //返回增量值  
}
 
int g_CurrentVelocity; 
int g_Flag;   

void main(void) 
{ 
    IncPIDInit(); 

    g_CurrentVelocity=0;  //全局变量也初始化 g_Flag=0;                
    While(1) 
    { 
        if (g_Flag& HAVE_NEW_VELOCITY) 
        { 
            PWMOUT += IncPIDCalc(CurrentVelocity);            
            g_Flag&=~ HAVE_NEW_VELOCITY; 
        }
    }
} 