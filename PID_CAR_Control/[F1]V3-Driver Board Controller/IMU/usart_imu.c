/* Includes ------------------------------------------------------------------*/
#include "usart_imu.h"
#include "motor_pcb_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Usart_PID_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; //NVIC - 嵌套向量中断控制器
	
	/* Enable USART1 clock for PID */
	RCC_APB2PeriphClockCmd(USART_PID_CLOCK, ENABLE);
	
	//Enable and set USART1 Interrupt the the second lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = PID_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Set GPIOs for USART1-PID */
	GPIO_InitStructure.GPIO_Pin = STM_PID_TX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(STM_PID_PORT, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin = STM_PID_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(STM_PID_PORT, &GPIO_InitStructure);  
	
	/* Usart1 Config */
	USART_InitStructure.USART_BaudRate = BAUDRATE_PID;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
	USART_Init(USART_PID_CHANNEL, &USART_InitStructure);   

	/* Set NVIC for PID-USART1 */
	// Interrupt while receiving data
	USART_ITConfig(USART_PID_CHANNEL, USART_IT_RXNE, DISABLE); //接收到信息中断
	USART_ITConfig(USART_PID_CHANNEL, USART_IT_TXE, ENABLE); //SEND到信息中断

	/* Enable USART1 */
	USART_Cmd(USART_PID_CHANNEL, ENABLE);
}

void Usart_JY901_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; //NVIC - 嵌套向量中断控制器
	
	/* Enable USART2clock for JY901 */
	RCC_APB1PeriphClockCmd(USART_JY901_CLOCK, ENABLE);
	
	//Enable and set USART2 Interrupt the the second lowest priority
	NVIC_InitStructure.NVIC_IRQChannel = JY901_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Set GPIOs for USART2-JY901 */
	GPIO_InitStructure.GPIO_Pin = STM_JY901_TX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(STM_JY901_PORT, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin = STM_JY901_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(STM_JY901_PORT, &GPIO_InitStructure);  
	
	/* Usart2 Config */
	USART_InitStructure.USART_BaudRate = BAUDRATE_JY901;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
	USART_Init(USART_JY901_CHANNEL, &USART_InitStructure);   

	/* Set NVIC for JY901-USART2 */
	// Interrupt while receiving data
	USART_ITConfig(USART_JY901_CHANNEL, USART_IT_RXNE, ENABLE); //接收到信息中断
	USART_ITConfig(USART_JY901_CHANNEL, USART_IT_TXE, DISABLE); //SEND到信息中断

	/* Enable USART2 */
	USART_Cmd(USART_JY901_CHANNEL, ENABLE);
}
