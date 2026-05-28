# Sistem-Radar-Ultrasonic
## 1. Introducere și Obiective
Prezentul proiect reprezintă un sistem embedded de monitorizare a mediului înconjurător prin tehnologie ultrasonică, implementat pe platforma hardware Arduino Nano. Obiectivul a fost crearea unei soluții integrate care combină achiziția de date în timp real, procesarea logică a acestora și vizualizarea grafică a mediului scanat.

Sistemul realizează:
* **Scanare activă:** Baleierea unui sector de 180° utilizând un servomotor.
* **Detecție:** Măsurarea distanței până la obiecte folosind senzorul ultrasonic HC-SR04.
* **Feedback local:** Alertare vizuală (LED-uri) și sonoră (buzzer) la detectarea obstacolelor.
* **Vizualizare:** Transmiterea datelor prin protocolul USART către o interfață grafică dezvoltată în Processing.



## 2. Arhitectura Software
Proiectul este dezvoltat modular în limbajul C, separând logic driverele hardware de nivel scăzut de logica aplicației.

### Folderul `/drivers` (Stratul Hardware)
* **`usart/`**: Implementarea comunicării seriale pentru transmiterea datelor către PC.
* **`timer/`**: Gestionează temporizarea pentru precizia senzorilor.
* **`gpio/`**: Abstractizează controlul pinilor digitali (LED-uri/Buzzer).
* **`pwm/`**: Utilizează modulația PWM pentru controlul servomotorului și al buzzer-ului.

### Folderul `/src` (Logica Aplicației)
* **`main.c`**: Punctul de intrare (Entry point). Coordonează inițializarea modulelor și conține bucla infinită de execuție (`super-loop`).
* **`alarma.c / .h`**: Gestionează pragurile de distanță. Implementează logica: `Verde (Liber) / Roșu + Buzzer (Obstacol la <30cm)`.
* **`comunicare.c / .h`**: Formatează și transmite datele prin USART în pachete de tip `unghi,distanta\n`.
* **`sensor_ultrasonic.c / .h`**: Calculează timpul de propagare a undei ultrasonice și transformă rezultatul în centimetri.
* **`servo_motor.c / .h`**: Controlează poziționarea unghiulară a senzorului.

## 3. Configurare Hardware (Pinout)
Conexiunile au fost stabilite pentru a permite utilizarea corectă a pinilor de tip PWM și Digital:

| Componentă | Pin Arduino Nano | Rol |
| :--- | :--- | :--- |
| **LED Verde** | D6 | Indicator stare "Safe" |
| **LED Roșu** | D7 | Indicator stare "Alertă" |
| **Buzzer** | D3 | Avertizare sonoră |
| **Senzor Ultrasonic** | Configurabil | Măsurare distanță |
| **Servo Motor** | Configurabil | Scanare unghiulară |



## 4. Fluxul de Funcționare
Sistemul parcurge un ciclu continuu:
1. **Poziționare:** Servomotorul rotește senzorul cu un pas unghiular.
2. **Achiziție:** Senzorul returnează distanța față de cel mai apropiat obiect.
3. **Decizie:** Modulul `alarma.c` analizează distanța. Dacă `d < 30cm`, se declanșează LED-ul Roșu și Buzzer-ul.
4. **Transmitere:** `comunicare.c` trimite datele către PC prin cablul USB.
5. **Afișare:** Interfața *Processing* primește datele, le decodează și desenează pe ecran „câmpul” radar, actualizând culorile în funcție de prezența obstacolelor.

## 5. Instrucțiuni de Utilizare

### Compilare și Programare (Arduino)
Utilizând terminalul VS Code:
1. `make clean` (Curăță fișierele binare anterioare).
2. `make all BOARD=nano` (Compilează întregul proiect).
3. `make flash` (Încarcă codul pe placa Arduino).
*Notă: Închideți terminalul după flash pentru a elibera portul COM.*

### Vizualizare (PC)
1. Deschideți mediul **Processing**.
2. Încărcați fișierul grafic `.pde`.
3. Asigurați-vă că portul serial (`Serial.list()[x]`) corespunde cu cel utilizat de Arduino Nano.
4. Apăsați butonul **Play** pentru a iniția radarul.

## 6. Concluzii
Acest proiect a permis înțelegerea modului în care hardware-ul și software-ul conlucrează pentru a forma un sistem embedded funcțional. Provocările întâmpinate în comunicarea serială și gestionarea resurselor au contribuit la dezvoltarea abilităților de debugging și arhitectură software.

STUDENTI: Cioponea Ionut-Sebastian
          Braitor Ana-Maria

GRUPA: AIA 3.1

FACULTATEA DE AUTOMATICA, CALCULATOARE SI ELECTRONICA
