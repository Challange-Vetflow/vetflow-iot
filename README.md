# VetFlow — Challenge FIAP 2026

Solução desenvolvida para o **Challenge FIAP 2026** em parceria com a **CLYVO VET**.

## Integrantes do Grupo

| Nome | RM | Turma |
|------|----|-------|
| Andrei de Paiva Gibbini | 563061 | 2TDSPF |
| Pedro Sakai Silva Zambaca | 565956 | 2TDSPF |
| Pedro Santos Pequini | 561842 | 2TDSPF |
| Arthur Câmara | 562310 | 2TDSPG |
| Diogo Cunha | 563654 | 2TDSPF |

# Monitoramento Clínico Veterinário IoT

Sistema de monitoramento clínico veterinário em tempo real, desenvolvido para otimizar o acompanhamento de pets internados. O sistema utiliza sensores integrados a um microcontrolador ESP32 que enviam dados de temperatura corporal e peso para um Dashboard interativo na nuvem, permitindo a detecção de alterações térmicas e monitoramento da evolução do peso.

## 🚀 Funcionalidades
- **Telemetria em Tempo Real:** Monitoramento de temperatura (DHT22) e peso (HX711).
- **Dashboard Visual:** Interface em tempo real utilizando Node-RED Dashboard.
- **Alertas Clínicos:** Notificações para estados de **Hipertermia** e **Hipotermia**.
- **Classificação Inteligente:** Identificação automática do porte do pet (Pequeno, Médio, Grande) baseada no peso.
- **Conectividade Segura:** Comunicação MQTT com criptografia TLS através do HiveMQ Cloud.

## 🛠 Tecnologias Utilizadas
- **Hardware:** ESP32, Sensor DHT22 (Temperatura), HX711 + Célula de Carga (Peso).
- **Protocolo:** MQTT (HiveMQ Cloud).
- **Backend/Dashboard:** Node-RED.
- **Simulação:** Wokwi.

## 📦 Estrutura do Projeto
- `sketch.ino`: Código-fonte para o ESP32 responsável pela leitura e transmissão dos sensores.
- `flows.json`: Arquivo de exportação do fluxo do Node-RED para importar no ambiente de monitoramento.

## ⚙️ Configuração
### 1. ESP32
- Certifique-se de ter as bibliotecas `PubSubClient`, `DHT sensor library` e `HX711 Arduino Library` instaladas na IDE (ou ambiente de simulação).
- Ajuste as variáveis `mqtt_server`, `mqtt_user` e `mqtt_pass` no arquivo `sketch.ino` com as credenciais do seu broker.

### 2. Node-RED
1. Importe o arquivo `flows.json` no seu editor Node-RED (Menu > Import).
2. Configure o nó de conexão MQTT (`mqtt_broker_config`) com as mesmas credenciais utilizadas no ESP32.
3. Verifique o **Layout** na aba Dashboard para garantir que os widgets de Gauge e Chart estejam organizados corretamente.
4. Clique em **Deploy**.

## 📊 Acesso ao Dashboard
Após o deploy, acesse a interface através do navegador:
`http://localhost:1880/ui`
