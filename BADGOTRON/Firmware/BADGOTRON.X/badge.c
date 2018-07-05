#include "badgotron.h"

t_wiegand_buf	g_wiegand_buf;
u8				g_id_badge[5];

void	init_wiegand(void)
{
	u8	tmp = 0;
	
	// Init buffer
	g_wiegand_buf.index = 0;
	__builtin_disable_interrupts(); // Desativer les interrupts partout
	AD1PCFGbits.PCFG4 = 1; //Force la pin en mode digital (car elle est AN aussi la salope
	AD1PCFGbits.PCFG5 = 1; // idem

	WIEGAND_DATA0_MODE = PIN_MODE_INPUT;
	WIEGAND_DATA1_MODE = PIN_MODE_INPUT;
	CNENbits.CNEN6 = 1; //Enable CN6 (cf datasheet CN6 = RB4)
	CNENbits.CNEN7 = 1;
	CNCONbits.ON = 1; //Enable CON (CN interrupts)

	////CNPUEbits.CNPUE7 = 1; -> pull up DESACTIVE
	// READ PORT BIT FOR CLEARING IT
	tmp += WIEGAND_DATA0_DATA;
	tmp += WIEGAND_DATA1_DATA;
	// INTERRUPT
	IPC6bits.CNIP = 7;
	IPC6bits.CNIS = 3;
	IFS1bits.CNIF = 0;
	IEC1bits.CNIE = 1;
	__builtin_enable_interrupts();
}
/* tested and working */
static u8	checksum_is_ok(void)
{
	u8	res;
	u8	checksum;
	u8	i;
	u8	j;
	u8	tmp;
	
	res = 0;
	checksum = 0;
	i = -1;
	while (++i < 4)
		checksum = (checksum << 1) + g_wiegand_buf.buffer[40 + i];
	i = 0;
	while (i < 40)
	{
		tmp = 0;
		j = -1;
		while (++j < 4)
			tmp = (tmp << 1) + g_wiegand_buf.buffer[i + j];
		res ^= tmp;
		i += 4;
	}
	if (res == checksum)
		return (1);
	return (0);
}
/*Tested working*/
void	badge_bitwise(void)
{
	u8	i;

	i = 0;
	g_id_badge[0] = 0;
	g_id_badge[1] = 0;
	g_id_badge[2] = 0;
	g_id_badge[3] = 0;
	g_id_badge[4] = 0;
	while (i < 40)
	{
		if (g_wiegand_buf.buffer[i] == 1)
			g_id_badge[i / 8] = g_id_badge[i / 8] | (u8)(1 << 7 - (i % 8));
		i++;
	}
}

void	start_badge(void)
{
	if (!checksum_is_ok())
	{
		display_clear();
		display_printstr("Erreur de lecture du badge");
		msleep(2000);
		display_clear();
		return ;
	}
	display_clear();
	display_printstr("Lecture du badge OK");
	msleep(2000);
	display_clear();
	badge_bitwise();
	id_cpy(g_flash_index.index.user[0].id, g_id_badge);
	g_flash_data.data.user[0].timestamp = 12345678;
	msleep(10);

	/*if (get_user_position() == -1)
		create_user();*/
}