#define LED_S_R 5
#define LED_S_Y 6
#define LED_S_G 7
#define BUTTON_S 2

#define LED_WT_R 8
#define LED_WT_Y 9
#define LED_WT_G 10
#define BUTTON_WT 3

#define LED_WK_G 11
#define LED_WK_R 12
#define BUTTON_WK 4

#define goS 0
#define waitS 1
#define goWt 2
#define waitWt 3
#define goWk 4
#define lightOn 5
#define lightOff 6
#define lightOff2 7

int input;
int inputS;
int inputWt;
int inputWk;

struct State
{
	unsigned long ST_Out;
	unsigned long Time;
	unsigned long Next[8];
} ;

typedef const struct State SType;

Stype FSM[7] = {
	{B00110001, 2000, {goS, waitS, waitS, waitS, goS, waitS, waitS, waitS}},
	{B01010001, 300, {goWt, goWt, goWt, goWt, goWt, goWt, goWt, goWt}},
	{B10000101, 2000, {goWt, waitWt, goWt, waitWt, waitWt, waitWt, waitWt, waitWt}},
	{B10001001, 300, {goWk, goWk, goWk, goWk, goWk, goWk, goWk, goWk}},
	{B10010010, 1500, {goWk, goWk, lightOff, lightOff, lightOff, lightOff, lightOff, lightOff}},
	{B10010010, 100, {lightOff2, lightOff2, lightOff2, lightOff2, lightOff2, lightOff2, lightOff2, lightOff2}},
	{B10010000, 100, {lightOn, lightOn, lightOn, lightOn, lightOn, lightOn, lightOn, lightOn}},
	{B10010000, 100, {goS, goS, lightOn, goS, goS, goS, goS, goS}},
};

unsinged long S = 0;

void setup()
{
	pinMode(LED_S_R, OUTPUT);
	pinMode(LED_S_Y, OUTPUT);
	pinMode(LED_S_G, OUTPUT);
	pinMode(BUTTON_S, INPUT_PULLUP);

	pinMode(LED_WT_R, OUTPUT);
	pinMode(LED_WT_Y, OUTPUT);
	pinMode(LED_WT_G, OUTPUT);
	pinMode(BUTTON_WT, INPUT_PULLUP);

	pinMode(LED_WK_G, OUTPUT);
	pinMode(LED_WK_R, OUTPUT);
	pinMode(BUTTON_WK, INPUT_PULLUP);
}

void loop()
{

	digitalWrite(LED_S_R, FSM[S].ST_Out & B10000000);
	digitalWrite(LED_S_Y, FSM[S].ST_Out & B01000000);
	digitalWrite(LED_S_G, FSM[S].ST_Out & B00100000);

	digitalWrite(LED_WT_R, FSM[S].ST_Out & B00010000);
	digitalWrite(LED_WT_Y, FSM[S].ST_Out & B00001000);
	digitalWrite(LED_WT_G, FSM[S].ST_Out & B00000100);

	digitalWrite(LED_WK_G, FSM[S].ST_Out & B0000010);
	digitalWrite(LED_WK_R, FSM[S].ST_Out & B00000001);

	delay(FSM[S].Time);

	inputS = digitalRead(BUTTON_S);
	inputWt = digitalRead(BUTTON_WT);
	inputWk = digitalRead(BUTTON_WK);

	input = 4*inputS + 2*inputWt + inputWk;
	S = FSM[S].Next[input];
}
