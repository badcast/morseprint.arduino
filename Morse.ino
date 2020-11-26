#define __DBG
const char message[] = {'П', 'Р', 'И', 'В', 'Е', 'Т', '\0'};
struct signal
{
  byte ch; //character
  char *rules; // rules
} ss[] = {
  {'А', "*-"},
  {'Б', "-***"},
  {'В', "*--"},
  {'Г', "--*"},
  {'Д', "-**"},
  {'Е', "*"},
  {'Ж', "***-"},
  {'З', "--**"},
  {'И', "**"},
  {'Й', "*---"},
  {'К', "-*-"},
  {'Л', "*-**"},
  {'М', "--"},
  {'Н', "-*"},
  {'О', "---"},
  {'П', "*--*"},
  {'Р', "*-*"},
  {'С', "***"},
  {'Т', "-"},
  {'У', "**-"},
  {'Ф', "**-*"},
  {'Х', "****"},
  {'Ц', "-*-*"},
  {'Ч', "---*"},
  {'Ш', "----"},
  {'Щ', "--*-"},
  {'Ъ', "*--*-*"},
  {'Ы', "-*--"},
  {'Ь', "-**-"},
  {'Э', "***-***"},
  {'Ю', "**--"},
  {'Я', "*-*-"}
};

void print_morzhe(const char* msg, int latency_ms = 569, int perSignal_ms = 128, int perSignalLine_ms = 360);

void setup() {
#ifdef _DBG
  Serial.begin(9600);
  for (; !Serial;);
#endif

  //Приготовить для вывода PIN
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
 print_morzhe(message);
}

//Показать морзе в ->
void print_morzhe(const char* msg, int latency_ms, int perSignal_ms, int perSignalLine_ms) {

  register byte i;
  register byte j, k;
  signal* pS;
  const byte len = strlen(msg);
  //подготовка
  digitalWrite(LED_BUILTIN, LOW);
  for (i = 0; i < len; ++i) {
    //Реализация пикания (морзе)
    j = (byte)msg[i];
    if (j >= static_cast<byte>('А') && j <= static_cast<byte>('Я'))
    {
      pS = &ss[j - (byte)'А'];
      k = strlen(pS->rules);
      //LED ON and LED OFF (PICKING)
      for (j = 0; j < k; ++j) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay( ((pS->rules[j] == '*' ) ? perSignal_ms : perSignalLine_ms));
        digitalWrite(LED_BUILTIN, LOW);
        delay( ((pS->rules[j] == '*' ) ? perSignal_ms : perSignalLine_ms));
        #ifdef _DBG
        Serial.print(pS->rules[j]);
        #endif
      }

    }
    else
    {
#ifdef _DBG
      Serial.println();
#endif
      //Задержка (latency)
      delay(latency_ms);

    }

  }
}
