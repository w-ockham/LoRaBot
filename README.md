# LoRaBot

[Arduino LoRa](https://github.com/sandeepmistry/arduino-LoRa/blob/master/README.md)���g���A430MHz�тŃ`���b�g���s�����Ƃ��ł���Arduino�X�P�b�`�ł��B

## �n�[�h�E�F�A

 * [Semtech SX1276/77/78/79](http://www.semtech.com/apps/product.php?pn=SX1276)���g�����{�[�h�œ��삵�܂��B:
   * [BSFrance LoRa32u4](https://bsfrance.fr/lora-long-range/1311-BSFrance-LoRa32u4-1KM-Long-Range-Board-Based-Atmega32u4-433MHz-LoRA-RA02-Module.html)

### Semtech SX1276/77/78/79 

| Semtech SX1276/77/78/79 | Arduino |
| :---------------------: | :------:|
| VCC | 3.3V |
| GND | GND |
| SCK | SCK |
| MISO | MISO |
| MOSI | MOSI |
| NSS | 8 |
| NRESET | 4 |
| DIO0 | 7 |


`NSS`,`NRESET`,`DIO0`��`LoRa.setPins(csPin, resetPin, irqPin)`. �Őڑ����邱�Ƃ��o���܂��B�{�[�h�ɂ���ăs���ڑ���ύX���ĉ������B

## �C���X�g�[�����@

### Arduino IDE��LoRa32u4�{�[�h��ǉ�
1. �t�@�C�������ݒ�ŁA�ǉ��̃{�[�h�}�l�[�W����URL�Ɉȉ���ǉ�  
   `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json`
2. �c�[�����{�[�h��`AdaFruit Feather32u4`��I��
3. �c�[�����������u��`ArduinoISP`��I��

### Arduino LoRa���C�u�����̒ǉ�
1. �c�[�������C�u�����}�l�[�W���ŁA`LoRa by Sandeep Mistry`��ǉ�

### �R���p�C���Ə�������
1. LoRaBot.ino���J��  
2. �X�P�b�`�����؁E�R���p�C���ŃR���p�C��  
3. �X�P�b�`���}�C�R���{�[�h�ɏ������ނ�Arduino�֏�������  

### �X�}�[�g�t�H���Ƃ̐ڑ�
1. �X�}�z��[USB�V���A���[��](https://play.google.com/store/apps/details?id=jp.sugnakys.usbserialconsole&hl=ja)���C���X�g�[��
2. [OTG�P�[�u��](https://www.amazon.co.jp/dp/B012V56C8K)��microUSB�P�[�u�����g����LoRa32u4���X�}�z�ɐڑ�
3. �V���A���|�[�g�̐ݒ��  
  �{�[���[�g9600 �f�[�^�r�b�g8 �p���e�Bnone �X�g�b�v�r�b�g1 �t���[����off  
  ��I��
4. �ڑ��̐ݒ�ő��M�t�H�[���̕\���A���s�R�[�hCR+LF��I��

## �g����
2���LoRa32u4�ɏ������݂܂��B�����[�g�������o�C���o�b�e�����ɁA���[�J�������X�}�z�ɐڑ����܂��B  
�f�t�H���g�ł�Bot���[�h�ŋN�����܂��B�N���C�A���g���͈ȉ��̃R�}���h�Ńm�[�}�����[�h�ɂ��Ă��������B
```sh
set mode norm
```
USB�[���\�t�g���烁�b�Z�[�W�𑗂��438.2MHz��LoRa�ϒ��Ń��b�Z�[�W�𑗂�܂��B  
�i�ۏؔF����󂯖Ƌ������܂ł͕K���_�~�[���[�h�����g���Ď������ĉ������j  
�f�t�H���g�ł͎��g��438.2MHz�ASF=10�ABW=31.25kHz �o��20dBm(100mW)�̐ݒ�ɂȂ��Ă��܂��B
```sh
set
Freq=438200000
SF=10
BW=4�@(31250Hz)
TXpower=20
```
�^�[�~�i�����烁�b�Z�[�W�����A�Ō�ɉ��s(CR/LF)����͂��ĉ������B
���b�Z�[�W�̑��M����������ƈȉ��̂悤�ɕ\������܂��B
```sh
 <�R�[���T�C��> >: <���M�������b�Z�[�W>
```
����ǂ��烁�b�Z�[�W����M����ƈȉ��̂悤�ɕ\������܂��B
```sh
 <����ǃR�[���T�C��> (<RSSI�l>,<SNR�l>,<���g���G���[�l>)<: <��M�������b�Z�[�W>
 ```
Bot���ł͑����ė������b�Z�[�W�Ɏ�M����RSSI(�M�����x)�ASNR�A���g���G���[�l�������ăI�E���Ԃ����܂��B
```sh
JL1NIE/1>:����ɂ��͂���̓e�X�g
JL1NIE(-88,11.75,1928)<:Hi JL1NIE UR Rprt RSSI=-89,SNR=11.25,Ferr=-1984. UR Msg JL1NIE/1>:����ɂ��͂���̓e�X�g.
```

## �R�}���h
### ���g���̐ݒ�
�^�p���g����Hz�Ŏw�肵�܂��B�w��ł���͈͂�438MHz-439MHz(�S�d�g�`���͈̔�)�ł��B
�f�t�H���g�l��438.2MHz�ł��B
```sh
 set freq 438200000
```
### ���M�o�͂̐ݒ�
���M�o�͂�dBm�Ŏw�肵�܂��B2dBm - 20dBm�͈̔͂ł��B
�f�t�H���g�l��20dBm�ł��B
```sh
 set pwr 20
```
### �g�U��(SF)�̎w��
�g�U��(Spreading Factor)���w�肵�܂��B6 - 12�͈̔͂ł��B
  �������l�قǍ����ɑ��M�ł��܂���SNR�ł͕s���ɂȂ�܂��B
  �f�t�H���g�l��10�ł��B
```sh
 set sf 10
```
### �ш敝(BW)�̎w��
�`���[�v�X�y�N�g�����̑ш敝���w�肵�܂��B0-8�͈̔͂ł��B
  �ш敝���L���قǍ����ɑ��M�ł��܂���SNR�ł͕s���ɂȂ�܂��B
  �f�t�H���g�l��4(31.25kHz)�ł��B
```sh
 set bw 4
 ```
| BW�l | �ш敝 |
|:-----|:-------|
|0 | 7.8kHz |
|1 | 10.4kHz |
|2 | 15.6kHz |
|3 | 20.8kHz |
|4 | 31.25kHz |
|5 | 41.7kHz |
|6 | 62.5kHz |
|7 | 125kHz |
|8 | 250kHz |

### ���샂�[�h�̎w��
�[���̓��샂�[�h���w�肵�܂��B
�f�t�H���g�l��BOT�ł��B
  �X�v���A�X���蓙�ŘA���M�����K�v�ȏꍇ��CONT���[�h���g���ĉ������B
```sh
set mode NORM
```
|���[�h| ���� |
|:----:|:----:|
|NORM | �ʏ탂�[�h|
|BOT  | ����ꂽ���b�Z�[�W��RSSI/SNR����t���ĕԂ�BOT�ɂȂ�܂�|
|CONT | 0fill���ꂽ�p�P�b�g(255byte)��A�����M���܂�|
|VERB | �o�̓��b�Z�[�W���璷�ɂ��܂�|

### ���ǃR�[���T�C���̎w��
���ǂ̃R�[���T�C�����w�肵�܂��B�p�P�b�g�擪�ɂ͕K�����ǃR�[���T�C��������܂��B
```sh
set call �R�[���T�C��
```

### �����[�g�[���̐ݒ�
LoRa�ł͑��M���E��M����SF/BW���̃p�����[�^�����v���Ă��Ȃ��ƌ�M���邱�Ƃ��ł��܂���B
`rset`�͎��ǂƋ��ɑ���Ǒ��̃p�����[�^�𓯎��ɕύX����R�}���h�ł��B
```sh
rset �R�}���h �p�����[�^
```
�R�}���h�E�p�����[�^��`set`�Ɠ����ł��B
�����[�g���[���͐V���ɕύX���ꂽ�p�����[�^�Ńe�X�g���M���s���܂��̂�
���[�J���[���Ő�������M�ł��邩�m�F���Ă��������B
```sh
JL1NIE/1>:rset sf 9
Set Spreading Factor = 9
JL1NIE(-90,9.75,1911)<:VVV VVV VVV
JL1NIE(-90,10.25,1913)<:VVV VVV VVV
JL1NIE(-90,9.75,1914)<:VVV VVV VVV
```

### �ݒ�̊m�F
`set`�R�}���h�Ńp�����[�^���w�肵�Ȃ��ƌ��݂̐ݒ�l���\������܂��B
```sh
Freq=438200000
SF=10
BW=4�@(31250Hz)
TXpower=20
```

### �ݒ�̏�����
�ݒ���f�t�H���g�l�ɖ߂��܂��B
```sh
set init
```

## ���C�Z���X
 Apache License 2.0�Ŕz�z���܂��B
