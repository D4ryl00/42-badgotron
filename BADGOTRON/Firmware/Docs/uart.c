/*******************************************************************************/
/* 			      		  	 UNIVERSITY OF AVEIRO				     		   */
/* 		   DEPARTMENT OF ELECTRONICS, TELECOMMUNICATIONS AND COMPUTERS	       */
/*									   &									   */ 
/* 						    DEPARTMENT OF MECHANICS 						   */
/* 				   	 PROJECT HUMANOID OF UNIVERSITY OF AVEIRO		      	   */
/*																			   */
/* AUTHOR: Miguel Antunes da Fonseca Ribeiro (36317)						   */
/* SUPERVISION: Filipe Silva (IEETA) 										   */
/* 				Vítor Santos (DEM)											   */
/*																			   */
/* FILE'S NAME: uart.c														   */
/* FILE'S DESCRIPTION: Source Code for UARTx module functions				   */
/*******************************************************************************/

#include "uart.h"

/*********************************************************************
* Function Name     : openUART1                                      *
* Description       : This function configures the UART mode,        * 
*                     UART Interrupt modes and the Baud Rate         *
* Parameters        : unsigned int oscfreq oscillator frequency      *
*                     unsigned int baud desired baud rate for 	 	 *
*						UART1 module 							     *
*					  unsigned int config configuration for			 *
*						UART1 module								 *
* Return Value      : None                                           *
*********************************************************************/
void openUART1(unsigned int oscfreq, unsigned int baud, unsigned int config)
{
	float brg;

	/* Calculate Baud Rate Generator Register value (U1BRG) */
	brg=((float) (oscfreq/2)*1e6)/((float) 4*baud)-1.0;
	if (brg-(unsigned int) brg>=0.5)  
		brg+=1.0;

	//Using Fosc = 10MHz use brg=65.0
	brg=65.0;
	U1BRG = (unsigned int) brg;

	U1MODE = config;	/* UART1 mode register */

	U1STAbits.UTXISEL0=1;
	U1STAbits.UTXISEL1=1;
	U1STAbits.UTXBRK = 0;
	U1STAbits.UTXINV =0;
	U1STAbits.OERR = 0;

	U1MODEbits.UARTEN = 1;			/* UART1 is enabled */
	U1STAbits.UTXEN=1;				/* UART1 Transmission enabled */
}

/*********************************************************************
* Function Name     : openUART2                                      *
* Description       : This function configures the UART mode,        *
*                     UART Interrupt modes and the Baud Rate         *
* Parameters        : unsigned int oscfreq oscillator frequency      *
*                     unsigned int baud desired baud rate for 	 	 *
*						UART2 module 							     *
*					  unsigned int config configuration for			 *
*						UART2 module								 *
* Return Value      : None                                           *      
*********************************************************************/
void openUART2(unsigned int oscfreq, unsigned int baud,unsigned int config)
{
	float brg;

	/* Calculate Baud Rate Generator Register value (U2BRG) */
	brg=((float) (oscfreq/2)*1e6)/((float) 4*baud)-1.0;
	if (brg-(unsigned int) brg>=0.5)  
		brg+=1.0;
	
	//Using Fosc = 10MHz use brg=65.0
	brg=65.0;	
	U2BRG = (unsigned int) brg;

	U2MODE = config;	/* UART2 mode register */

	U2STAbits.UTXISEL0=1;
	U2STAbits.UTXISEL1=1;
	U2STAbits.UTXBRK = 0;
	U2STAbits.UTXINV =0;
	U2STAbits.OERR = 0;

	U2MODEbits.UARTEN = 1;			/* UART1 is enabled */
	U2STAbits.UTXEN=1;				/* UART1 Transmission enabled */
}

/*********************************************************************
* Function Name     : closeUART1                                     *
* Description       : This function disables the UART and clears the *
*                     Interrupt enable & flag bits                   *  
* Parameters        : None                                           *
* Return Value      : None                                           *  
*********************************************************************/
void closeUART1(void)
{  
	/* Disable UART1 */
    U1MODEbits.UARTEN = 0;
	
	/* Clear interrupt enable bits */
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
	
	/* Clear IF flags */
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
}

/*********************************************************************
* Function Name     : closeUART2                                     *
* Description       : This function disables the UART and clears the *
*                     Interrupt enable & flag bits                   *  
* Parameters        : None                                           *
* Return Value      : None                                           *  
*********************************************************************/
void closeUART2(void)
{  
	/* Disable UART2 */
    U2MODEbits.UARTEN = 0;
	
	/* Clear interrupt enable bits */
    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;
	
	/* Clear IF flags */
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;
}

/**********************************************************************
* Function Name     : configIntUART1                                  *
* Description       : This function sets priority for RX,TX interrupt * 
*                     and enable/disables the interrupt               *
* Parameters        : None											  *
* Return Value      : None                                            *  
**********************************************************************/
void configIntUART1(unsigned int rxprior, unsigned int txprior)
{
    /* Clear IF flags */
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;

    /* Set priority */
    IPC2bits.U1RXIP = rxprior & 0x7;
    IPC3bits.U1TXIP = txprior & 0x7;

    /* Enable/disable interrupt */
    IEC0bits.U1RXIE = 1;	/* UART1 Receiver Interrupt enabled */
    IEC0bits.U1TXIE = 1;	/* UART1 Transmitter Interrupt enabled */
}

/**********************************************************************
* Function Name     : configIntUART2                                  *
* Description       : This function sets priority for  RX and TX      *
*                     interrupt and enable/disables the interrupt     *  
* Parameters        : None											  *
* Return Value      : None                                            *
**********************************************************************/
void configIntUART2(unsigned int rxprior, unsigned int txprior)
{
    /* Clear IF flags */
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;

    /* Set priority */
    IPC7bits.U2RXIP = rxprior & 0x7;
    IPC7bits.U2TXIP = txprior & 0x7;

    /* Enable/disable interrupt */
    IEC1bits.U2RXIE = 1;	/* UART2 Receiver Interrupt enabled */
    IEC1bits.U2TXIE = 1;	/* UART2 Transmitter Interrupt enabled */
}

/*************************************************************************
* Function Name     : busyUART1                                          *
* Description       : This returns status whether the transmission       *
*                     is in progress or not, by checking Status bit TRMT *
* Parameters        : None                                               *
* Return Value      : Info about whether transmission is in progress.    *
*					  True -> Busy ; False -> Not Busy					 *
*************************************************************************/
boolean busyUART1(void)
{  
    return(!U1STAbits.TRMT);
}

/*************************************************************************
* Function Name     : busyUART2                                          *
* Description       : This returns status whether the transmission       *  
*                     is in progress or not, by checking Status bit TRMT *
* Parameters        : None                                               *
* Return Value      : Info about whether transmission is in progress.    *
*					  True -> Busy ; False -> Not Busy					 *
*************************************************************************/
boolean busyUART2(void)
{  
    return(!U2STAbits.TRMT);
}

/*********************************************************************
* Function Name     : dataRdyUart1                                   *
* Description       : This function checks whether there is any data *
*                     that can be read from the input buffer, by     *
*                     checking URXDA bit                             *
* Parameters        : None                                           *
* Return Value      : char if any data available in buffer           *
*					  True -> Data Ready ; False -> Data Not Ready   *
*********************************************************************/
boolean dataRdyUART1(void)
{    
	return(U1STAbits.URXDA);
}

/*********************************************************************
* Function Name     : dataRdyUart2                                   *
* Description       : This function checks whether there is any data *
*                     that can be read from the input buffer, by     *
*                     checking URXDA bit                             *
* Parameters        : None                                           *
* Return Value      : char if any data available in buffer           *
*					  True -> Data Ready ; False -> Data Not Ready   *
*********************************************************************/
boolean dataRdyUART2(void)
{
     return(U2STAbits.URXDA);
}

/******************************************************************************
* Function Name     : getsUART1                                               *
* Description       : This function gets a string of data of specified length * 
*                     if available in the UxRXREG buffer into the buffer      *
*                     specified.                                              *
* Parameters        : unsigned int length the length expected                 *
*                     unsigned int *buffer  the received data to be           * 
*                                  recorded to this array                     *
*                     unsigned int uart_data_wait timeout value               *
* Return Value      : unsigned int number of data bytes yet to be received    *
******************************************************************************/
void getsUART1(unsigned char *buffer)
{
    unsigned char * temp_ptr = (unsigned char *)buffer;
	unsigned char ch = '0';
	unsigned int flag=1;

    while(ch!=ENTER)           /* read till length is 0 */
    {
        while(!dataRdyUART1());
       	ch = U1RXREG & 0xFF; /* data byte from HW buffer to SW buffer */
		
		switch(ch)
		{
			case ENTER:	break;
			
			case BACKSPACE: *temp_ptr--;
							break;

			default:	if(!flag)
							*temp_ptr++=ch;
						else if(ch!='0')
						{
							*temp_ptr++=ch;
							flag=0;
						}	
		}
    }
	*temp_ptr='\0';
}

/******************************************************************************
* Function Name     : getsUART2                                               *
* Description       : This function gets a string of data of specified length * 
*                     if available in the UxRXREG buffer into the buffer      *
*                     specified.                                              *
* Parameters        : unsigned int length the length expected                 *
*                     unsigned int *buffer  the received data to be           * 
*                                  recorded to this array                     *
*                     unsigned int uart_data_wait timeout value               *
* Return Value      : unsigned int number of data bytes yet to be received    * 
******************************************************************************/
void getsUART2(unsigned char *buffer)
{
    unsigned char * temp_ptr = (unsigned char *)buffer;
	unsigned char ch = '0';
	unsigned int flag=1;

    while(ch!=ENTER)           /* read till length is 0 */
    {
        while(!dataRdyUART2());
       	ch = U2RXREG & 0xFF; /* data byte from HW buffer to SW buffer */
		
		switch(ch)
		{
			case ENTER:	break;
			
			case BACKSPACE: *temp_ptr--;
							break;

			default:	if(!flag)
							*temp_ptr++=ch;
						else if(ch!='0')
						{
							*temp_ptr++=ch;
							flag=0;
						}	
		}
    }
	*temp_ptr='\0';
}

/***************************************************************************
* Function Name     : putsUART1                                            *
* Description       : This function puts the data string to be transmitted *
*                     into the transmit buffer (till NULL character)       *
* Parameters        : unsigned int * address of the string buffer to be    *  
*                     transmitted                                          *
* Return Value      : None                                                 *
***************************************************************************/
void putsUART1(unsigned char * buffer)
{
    char * temp_ptr = (char *) buffer;

    while(*temp_ptr != '\0')
    {
        while(U1STAbits.UTXBF);  /* wait if the buffer is full */
        U1TXREG = *temp_ptr++;   /* transfer data byte to TX reg */
    }
}

/***************************************************************************
* Function Name     : putsUART2                                            *
* Description       : This function puts the data string to be transmitted *
*                     into the transmit buffer (till NULL character)       * 
* Parameters        : unsigned int * address of the string buffer to be    *
*                     transmitted                                          *
* Return Value      : None                                                 *  
***************************************************************************/
void putsUART2(unsigned char * buffer)
{
    char * temp_ptr = (char *) buffer;

    while(*temp_ptr != '\0')
    {
        while(U2STAbits.UTXBF);  /* wait if the buffer is full */
        U2TXREG = *temp_ptr++;   /* transfer data byte to TX reg */
	}
}

/***************************************************************************
* Function Name     : readUART1                                            *
* Description       : This function returns the contents of UxRXREG buffer * 
* Parameters        : None                                                 *
* Return Value      : unsigned int value from UxRXREG receive buffer       *
***************************************************************************/
unsigned char readUART1(void)
{
	while(!dataRdyUART1());
    return (U1RXREG & 0xFF);
}

/***************************************************************************
* Function Name     : readUART2                                            *
* Description       : This function returns the contents of UxRXREG buffer *
* Parameters        : None                                                 *  
* Return Value      : unsigned int value from UxRXREG receive buffer       * 
***************************************************************************/
unsigned char readUART2(void)
{
	while(!dataRdyUART2());
    return (U2RXREG & 0xFF);
}

/*********************************************************************
* Function Name     : writeUART1                                     *
* Description       : This function writes data into the UxTXREG,    *
* Parameters        : unsigned int data the data to be written       *
* Return Value      : None                                           *
*********************************************************************/
void writeUART1(unsigned char data)
{
	while(busyUART1());
    U1TXREG = data & 0xFF;
}

/*********************************************************************
* Function Name     : writeUART2                                     *
* Description       : This function writes data into the UxTXREG,    *
* Parameters        : unsigned int data the data to be written       *
* Return Value      : None                                           *
*********************************************************************/
void writeUART2(unsigned char data)
{
	while(busyUART2());
    U2TXREG = data & 0xFF;  
}

/*********************************************************************
* Function Name     : len           		                         *
* Description       : This function checks the length of a buffer    *
* Parameters        : unsigned char buffer						     *
* Return Value      : None                                           *
*********************************************************************/
unsigned int len(unsigned char * buffer)
{
	unsigned int length=0;

	while(*buffer++ != '\0')
		length++;

	return length;		
}

unsigned int getIntUART1(void)
{
	unsigned char buf[10];
	getsUART1(buf);	
	return (ascii2int(buf));
}

unsigned int getIntUART2(void)
{
	unsigned char buf[10];
	getsUART2(buf);	
	return (ascii2int(buf));
}

void int2ascii(unsigned int val, unsigned char * buffer)
{
	unsigned int i, aux, flag=0;
	unsigned char * buf = (unsigned char *) buffer;

	for(i=10000;i>=1;i=i/10)
	{
		aux=val/i;
		if(aux!=0 || flag || i==1)
		{
			*buf++=(unsigned char)aux + '0';
			flag=1;
		}
		val = val-aux*i; 		
	}
	*buf='\0';
}

unsigned int ascii2int(unsigned char * buffer)
{
	unsigned int val=0, aux=0;
	unsigned char * buf = (unsigned char *) buffer;

	while(*buf != '\0')
	{
		aux=(unsigned int)(*buf-'0');
		val=val*10;
		val+=aux;	
		*buf++;
	}
	return val;
}

unsigned int ascii2hex(unsigned char * buffer)
{
	unsigned int val=0, aux=0;
	unsigned char * buf = (unsigned char *) buffer;

	while(*buf != '\0')
	{
		aux=(unsigned int)*buf;

		if(aux>='0' && aux<='9')
			aux=(unsigned int)(*buf-'0');
		else if(aux>='A' && aux<='F')
			aux=(unsigned int)(*buf-'A'+10);
		else if(aux>='a' && aux<='f')
			aux=(unsigned int)(*buf-'a'+10);

		val=val*16;
		val+=aux;	
		*buf++;
	}
	return val;
}

void hex2ascii(unsigned int val, unsigned char * buffer)
{
	unsigned int i, aux, flag=0;
	unsigned char * buf = (unsigned char *) buffer;
	
	for(i=0x1000;i>=0x1;i=i/0x10)
	{
		aux=val/i;
		if(aux!=0 || flag || i==0x1)
		{
			if(aux>=0x00 && aux<=0x09)
				*buf=(aux+'0');
			else if(aux>=0x0A && aux<=0x0F)
				*buf=(aux+'A'-0x0A);
			flag=1;
			*buf++;	
		}
		val = val-aux*i; 	
	}
	*buf='\0';
}

void putIntUART1(unsigned int val)
{
	unsigned char buf[10];

	int2ascii(val,buf);
	putsUART1(buf);
}

void putIntUART2(unsigned int val)
{
	unsigned char buf[10];

	int2ascii(val,buf);
	putsUART2(buf);
}

unsigned int getHexUART1(void)
{
	unsigned char buf[10];
	getsUART1(buf);	
	return (ascii2hex(buf));
}

unsigned int getHexUART2(void)
{
	unsigned char buf[10];
	getsUART2(buf);	
	return (ascii2hex(buf));
}

void putHexUART1(unsigned int val)
{
	unsigned char buf[10];
	hex2ascii(val,buf);
	putsUART1(buf);
}

void putHexUART2(unsigned int val)
{
	unsigned char buf[10];
	hex2ascii(val,buf);
	putsUART2(buf);
}
