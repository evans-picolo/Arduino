/*
 * Timer 1
 * 
 * Código para contar o tempo entre pulsos utilizando interrupção.
 * 
 * Evans Picolo
 * Asthor Barden
 * jun/2021
 * 
 */


// ===== CONSTANTES ===============================================================================================

const int DEBOUNCE = 100;   // tempo em ms para debounce do sensor


// ===== VARIÁVEIS GLOBAIS ========================================================================================

unsigned long int tempoFinal = 0;
unsigned long int tempoInicial = 0;
unsigned long int tempoDecorrido = 0;


// ===== PROTÍTIPOS ==============================================================================================

void marcaTempo();    // [ISR] Marca um tempo novo atualizando o valor da variável tempoFinal


// ===== CONFIGURAÇÕES INICIAIS ==================================================================================

void setup()
{
    // Inicia comunicação serial
    Serial.begin(9600);
    
    // Habilita INT0 (pino 2)
    // ISR: marcaTempo()
    // Acionamento em borda de subida
    attachInterrupt(0, marcaTempo, RISING);
}


// ===== PROGRAMA PRINCIPAL ======================================================================================

void loop()
{
    // Verifica se houve uma nova marcação de tempo
    if(tempoFinal != tempoInicial)
    {
        // Calcula o tempo decorrido
        tempoDecorrido = tempoFinal - tempoInicial;
                                                                                                                  
        // Veririca se esse tempo é maior que o debounce
        if(tempoDecorrido > DEBOUNCE)
        {
            // Envia o tempo decorrido para o serial
            Serial.println(tempoDecorrido);

            // Atualiza tempo inicial para a próxima marcação
            tempoInicial = tempoFinal;
        }
    }
}


// ===== INTERRUPÇÃO =============================================================================================

void marcaTempo()
{
    tempoFinal = millis();;
}
