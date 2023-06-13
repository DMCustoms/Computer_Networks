//Программа моделирует инкапсуляцию в эталонной модели OSI
//Упражнение 37 к первой главе книги Э.Таненбаума "Компьютерные сети"

#include <iostream>
#include <string.h>

using namespace std;

const int MAX_LENGTH = 80;//максимальный размер сообщения
const int MAX_HEADER_LENGTH = 64;//максимальный размер всех заголовков

void layer7_application(char[], size_t);

int main(){
   char message[MAX_LENGTH + 1];//первоначальное сообщение
   cout << "Enter message:" << "\n";
   fgets(message, MAX_LENGTH, stdin);//ввод первоначального сообщения
   layer7_application(message, strlen(message));//вызов функции прикладного уровня
   return 0;
}

void layer1_physical(char frame[], size_t size){
   //функция физического уровня
   //на этом уровне биты передаются по физической среде
   char bits[size];
   strcpy(bits, frame);
   printf("Transmit bits to the physical environment: %s", bits);
}

void layer2_data_link(char packet[], size_t size){ 
   //функция уровня передачи данных
   //Frame(кадр) - фрагмент данных уровня передачи данных
   char frame[MAX_HEADER_LENGTH + MAX_LENGTH + 1];
   strcpy(frame, "Header_2_");//добавление заголовка уровня
   strcat(frame, packet);
   printf("Frame on Data-link layer: %s", frame);
   layer1_physical(frame, strlen(frame));//вызов функции физического уровня
}

void layer3_network(char tpdu[], size_t size){ 
   //функция сетевого уровня
   //Packet - фрагмент данных протокола транспортного уровня
   char packet[MAX_HEADER_LENGTH + MAX_LENGTH + 1];
   strcpy(packet, "Header_3_");//добавление заголовка уровня
   strcat(packet, tpdu);
   printf("Packet on Network layer: %s", packet);
   layer2_data_link(packet, strlen(packet));//вызов функции уровня передачи данных
}

void layer4_transport(char spdu[], size_t size){ 
   //функция транспортного уровня
   //TPDU - Transport Protocol Data Unit - фрагмент данных протокола транспортного уровня
   char tpdu[MAX_HEADER_LENGTH + MAX_LENGTH + 1];
   strcpy(tpdu, "Header_4_");//добавление заголовка уровня
   strcat(tpdu, spdu);
   printf("TPDU on Transport layer: %s", tpdu);
   layer3_network(tpdu, strlen(tpdu));//вызов функции сетевого уровня
}

void layer5_session(char ppdu[], size_t size){
   //функция сеансового уровня
   //SPDU - Session Protocol Data Unit - фрагмент данных протокола сеансового уровня
   char spdu[MAX_HEADER_LENGTH + MAX_LENGTH + 1];
   strcpy(spdu, "Header_5_");//добавление заголовка уровня
   strcat(spdu, ppdu);
   printf("SPDU on Session layer: %s", spdu);
   layer4_transport(spdu, strlen(spdu));//вызов функции транспортного уровня
}

void layer6_presentation(char apdu[], size_t size){
   //функция уровня представления
   //PPDU - Application Protocol Data Unit - фрагмент данных протокола уровня представления
   char ppdu[MAX_HEADER_LENGTH + MAX_LENGTH + 1];
   strcpy(ppdu, "Header_6_");//добавление заголовка уровня
   strcat(ppdu, apdu);
   printf("PPDU on Presentation layer: %s", ppdu);
   layer5_session(ppdu, strlen(ppdu));//вызов функции сеансового уровня
}

void layer7_application(char apdu[], size_t size) {
   //функция прикладного уровня
   //APDU - Application Protocol Data Unit - фрагмент данных протокола прикладного уровня
   printf("APDU on Application layer: %s", apdu);
   layer6_presentation(apdu, size);//вызов функции уровня представления
}

