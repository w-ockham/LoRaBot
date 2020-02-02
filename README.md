# LoRaBot

[Arduino LoRa](https://github.com/sandeepmistry/arduino-LoRa/blob/master/README.md)を使い、430MHz帯でチャットを行うことができるArduinoスケッチです。

## ハードウェア

 * [Semtech SX1276/77/78/79](http://www.semtech.com/apps/product.php?pn=SX1276)を使ったボードで動作します。:
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


`NSS`,`NRESET`,`DIO0`は`LoRa.setPins(csPin, resetPin, irqPin)`. で接続することが出来ます。ボードによってピン接続を変更して下さい。

## インストール方法

### Arduino IDEにLoRa32u4ボードを追加
1. ファイル→環境設定で、追加のボードマネージャのURLに以下を追加  
   `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json`
2. ツール→ボードで`AdaFruit Feather32u4`を選択
3. ツール→書込装置で`ArduinoISP`を選択

### Arduino LoRaライブラリの追加
1. ツール→ライブラリマネージャで、`LoRa by Sandeep Mistry`を追加

### コンパイルと書き込み
1. LoRaBot.inoを開く  
2. スケッチ→検証・コンパイルでコンパイル  
3. スケッチ→マイコンボードに書き込むでArduinoへ書き込み  

### スマートフォンとの接続
1. スマホに[USBシリアル端末](https://play.google.com/store/apps/details?id=jp.sugnakys.usbserialconsole&hl=ja)をインストール
2. [OTGケーブル](https://www.amazon.co.jp/dp/B012V56C8K)とmicroUSBケーブルを使ってLoRa32u4をスマホに接続
3. シリアルポートの設定で  
  ボーレート9600 データビット8 パリティnone ストップビット1 フロー制御off  
  を選択
4. 接続の設定で送信フォームの表示、改行コードCR+LFを選択

## 使い方
2台のLoRa32u4に書き込みます。リモート側をモバイルバッテリ等に、ローカル側をスマホに接続します。  
デフォルトではBotモードで起動します。クライアント側は以下のコマンドでノーマルモードにしてください。
```sh
set mode norm
```
USB端末ソフトからメッセージを送ると438.2MHzでLoRa変調でメッセージを送ります。  
（保証認定を受け免許されるまでは必ずダミーロード等を使って実験して下さい）  
デフォルトでは周波数438.2MHz、SF=10、BW=31.25kHz 出力20dBm(100mW)の設定になっています。
```sh
set
Freq=438200000
SF=10
BW=4　(31250Hz)
TXpower=20
```
ターミナルからメッセージを入れ、最後に改行(CR/LF)を入力して下さい。
メッセージの送信が完了すると以下のように表示されます。
```sh
 <コールサイン> >: <送信したメッセージ>
```
相手局からメッセージを受信すると以下のように表示されます。
```sh
 <相手局コールサイン> (<RSSI値>,<SNR値>,<周波数エラー値>)<: <受信したメッセージ>
 ```
Bot側では送られて来たメッセージに受信時のRSSI(信号強度)、SNR、周波数エラー値を加えてオウム返しします。
```sh
JL1NIE/1>:こんにちはこれはテスト
JL1NIE(-88,11.75,1928)<:Hi JL1NIE UR Rprt RSSI=-89,SNR=11.25,Ferr=-1984. UR Msg JL1NIE/1>:こんにちはこれはテスト.
```

## コマンド
### 周波数の設定
運用周波数をHzで指定します。指定できる範囲は438MHz-439MHz(全電波形式の範囲)です。
デフォルト値は438.2MHzです。
```sh
 set freq 438200000
```
### 送信出力の設定
送信出力をdBmで指定します。2dBm - 20dBmの範囲です。
デフォルト値は20dBmです。
```sh
 set pwr 20
```
### 拡散率(SF)の指定
拡散率(Spreading Factor)を指定します。6 - 12の範囲です。
  小さい値ほど高速に送信できますがSNRでは不利になります。
  デフォルト値は10です。
```sh
 set sf 10
```
### 帯域幅(BW)の指定
チャープスペクトラムの帯域幅を指定します。0-8の範囲です。
  帯域幅が広いほど高速に送信できますがSNRでは不利になります。
  デフォルト値は4(31.25kHz)です。
```sh
 set bw 4
 ```
| BW値 | 帯域幅 |
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

### 動作モードの指定
端末の動作モードを指定します。
デフォルト値はBOTです。
  スプリアス測定等で連続信号が必要な場合はCONTモードを使って下さい。
```sh
set mode NORM
```
|モード| 動作 |
|:----:|:----:|
|NORM | 通常モード|
|BOT  | 送られたメッセージにRSSI/SNR等を付けて返すBOTになります|
|CONT | 0fillされたパケット(255byte)を連続送信します|
|VERB | 出力メッセージを冗長にします|

### 自局コールサインの指定
自局のコールサインを指定します。パケット先頭には必ず自局コールサインが入ります。
```sh
set call コールサイン
```

### リモート端末の設定
LoRaでは送信側・受信側のSF/BW等のパラメータが合致していないと交信することができません。
`rset`は自局と共に相手局側のパラメータを同時に変更するコマンドです。
```sh
rset コマンド パラメータ
```
コマンド・パラメータは`set`と同じです。
リモート側端末は新たに変更されたパラメータでテスト送信を行いますので
ローカル端末で正しく受信できるか確認してください。
```sh
JL1NIE/1>:rset sf 9
Set Spreading Factor = 9
JL1NIE(-90,9.75,1911)<:VVV VVV VVV
JL1NIE(-90,10.25,1913)<:VVV VVV VVV
JL1NIE(-90,9.75,1914)<:VVV VVV VVV
```

### 設定の確認
`set`コマンドでパラメータを指定しないと現在の設定値が表示されます。
```sh
Freq=438200000
SF=10
BW=4　(31250Hz)
TXpower=20
```

### 設定の初期化
設定をデフォルト値に戻します。
```sh
set init
```

## ライセンス
 Apache License 2.0で配布します。
