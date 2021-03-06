#ifndef PINCOMBOBOX_H
#define PINCOMBOBOX_H

#include <QWidget>

#include "deviceconfig.h"
#include "global.h"

#define PINS_COUNT 30
#define PIN_TYPE_COUNT 27
enum // разделить и вынести отдельно?                 // все структуры в global.h?
{
  PA_0 = 1,
  PA_1,
  PA_2,
  PA_3,
  PA_4,
  PA_5,
  PA_6,
  PA_7,
  PA_8,
  PA_9,
  PA_10,
  PA_15,

  PB_0,
  PB_1,
  PB_3,
  PB_4,
  PB_5,
  PB_6,
  PB_7,
  PB_8,
  PB_9,
  PB_10,
  PB_11,
  PB_12,
  PB_13,
  PB_14,
  PB_15,

  PC_13,
  PC_14,
  PC_15,

  ANALOG_IN,
  FAST_ENCODER_PIN,
  LED_PWM_PIN,

  I2C1_SDA,
  I2C1_SCL,
  I2C2_SDA,
  I2C2_SCL,

  SPI1_MOSI,
  SPI1_MISO,
  SPI1_SCK,
  SPI1_NSS,
  SPI2_MOSI,
  SPI2_MISO,
  SPI2_SCK,
  SPI2_NSS,

  ALL = 999,
};

struct cBox
{
    int deviceEnumIndex;
    QString guiName;
    int pinType[10];
    int pinExcept[10];
    int interaction[10];
    QString styleSheet; // стиль взаимодействия
};

struct pins
{
    int pin;
    QString objectName;
    QString guiName;
    int pinType[10];
};

namespace Ui {
class PinComboBox;
}

class PinComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit PinComboBox(uint pinNumber, QWidget *parent = nullptr);
    ~PinComboBox();

    //! return pointer to the first element, size=PINS_COUNT
    const pins *pinList() const;
    int currentDevEnum() const;
    //! номер элемента в pin_types
    const QVector<int> &pinTypeIndex() const;
    //! device enum присутствующие в комбобоксе
    const QVector<int> &enumIndex() const;

    uint interactCount() const;
    void setInteractCount(const uint &count);
    bool isInteracts() const;

    void setIndexStatus(int index, bool status);
    //void SetIndex();
    void resetPin();
    void setIndex_iteraction(int index, int senderIndex);
    void initializationPins(uint pin);
    void readFromConfig(uint pin);
    void writeToConfig(uint pin);

    void retranslateUi();

signals:
    void valueChangedForInteraction(int index, int senderIndex, int pin);
    void currentIndexChanged(int currentDeviceEnum, int previousDeviceEnum, int pinNumber);
private slots:
    void indexChanged(int index);

private:
    Ui::PinComboBox *ui;

    int m_currentDevEnum;
    int m_pinNumber;
    //! номер элемента в pin_types
    QVector<int> m_pinTypesIndex;
    //! device enum присутствующие в комбобоксе
    QVector<int> m_enumIndex;
    int m_previousIndex;

    bool m_isCall_Interaction;
    bool m_isInteracts;
    uint m_interactCount;
    int m_call_interaction;
    QString m_styleSheetDefault;

    ////////////////////////////// СЛИШКОМ ЖИРНО СДЕЛАТЬ static!!///////////////////////
    const pins m_pinList[PINS_COUNT] = // каждый пин хранит по структуре. а жирно не будет?
    {
        {PA_0,  {"A0"},    {tr("Pin A0")},     {ANALOG_IN}}, // пин // GUI name // его типы
        {PA_1,  {"A1"},    {tr("Pin A1")},     {ANALOG_IN}}, // добавить SERIAL, PWM...
        {PA_2,  {"A2"},    {tr("Pin A2")},     {ANALOG_IN}},
        {PA_3,  {"A3"},    {tr("Pin A3")},     {ANALOG_IN}},
        {PA_4,  {"A4"},    {tr("Pin A4")},     {ANALOG_IN}},
        {PA_5,  {"A5"},    {tr("Pin A5")},     {ANALOG_IN}},
        {PA_6,  {"A6"},    {tr("Pin A6")},     {ANALOG_IN}},
        {PA_7,  {"A7"},    {tr("Pin A7")},     {ANALOG_IN}},
        {PA_8,  {"A8"},    {tr("Pin A8")},     {}},
        {PA_9,  {"A9"},    {tr("Pin A9")},     {}},
        {PA_10, {"A10"},   {tr("Pin A10")},    {}},
        {PA_15, {"A15"},   {tr("Pin A15")},    {SPI1_NSS}},
        {PB_0,  {"B0"},    {tr("Pin B0")},     {}},
        {PB_1,  {"B1"},    {tr("Pin B1")},     {}},
        {PB_3,  {"B3"},    {tr("Pin B3")},     {SPI1_SCK}},
        {PB_4,  {"B4"},    {tr("Pin B4")},     {SPI1_MISO}},
        {PB_5,  {"B5"},    {tr("Pin B5")},     {SPI1_MOSI}},
        {PB_6,  {"B6"},    {tr("Pin B6")},     {}},
        {PB_7,  {"B7"},    {tr("Pin B7")},     {}},
        {PB_8,  {"B8"},    {tr("Pin B8")},     {I2C1_SCL}},
        {PB_9,  {"B9"},    {tr("Pin B9")},     {I2C1_SDA}},
        {PB_10, {"B10"},   {tr("Pin B10")},    {I2C2_SCL}},
        {PB_11, {"B11"},   {tr("Pin B11")},    {I2C2_SDA}},
        {PB_12, {"B12"},   {tr("Pin B12")},    {}},
        {PB_13, {"B13"},   {tr("Pin B13")},    {}},
        {PB_14, {"B14"},   {tr("Pin B14")},    {}},
        {PB_15, {"B15"},   {tr("Pin B15")},    {}},
        {PC_13, {"C13"},   {tr("Pin C13")},    {}},
        {PC_14, {"C14"},   {tr("Pin C14")},    {}},
        {PC_15, {"C15"},   {tr("Pin C15")},    {}},
    };

    const cBox m_pinTypes[PIN_TYPE_COUNT] = // static ?
    {
        {NOT_USED,       tr("Not Used"),
        {ALL},
        {},
        {}, {}},

        {BUTTON_GND,     tr("Button Gnd"),      // контроллер enum,  имя в ui   tr(нужен перевод)
        {ALL},                                  // добавление в конкретный пин или пины типа
        {},                                     // исключая пины
        {}, {"color: rgb(150, 155, 55);"}},     // взаимодействие с другими типами // стиль color, background-color, border-color...

        {BUTTON_VCC,     tr("Button Vcc"),
        {ALL},
        {},
        {}, {"color: rgb(170, 25, 25);"}},

        {BUTTON_ROW,     tr("Button Row"),
        {ALL},
        {},
        {}, {"color: rgb(25, 130, 220);"}},

        {BUTTON_COLUMN,  tr("Button Column"),
        {ALL},
        {},
        {}, {"color: rgb(120, 130, 250);"}},

        {SHIFT_REG_LATCH,tr("ShiftReg LATCH"),
        {ALL},
        {SPI1_SCK},
        {SPI_SCK}, {"color: rgb(53, 153, 120);"}},

        {SHIFT_REG_DATA, tr("ShiftReg DATA"),
        {ALL},
        {SPI1_SCK},
        {SPI_SCK}, {"color: rgb(53, 153, 120);"}},

        {TLE5011_CS,     tr("TLE5011 CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI},  // check  PB_6
        {SPI_SCK, SPI_MOSI, TLE5011_GEN}, {"color: rgb(53, 153, 120);"}},

        {TLE5012_CS,     tr("TLE5012B CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI},
        {SPI_SCK, SPI_MOSI, TLE5011_GEN}, {"color: rgb(53, 153, 120);"}},

        {MCP3201_CS,     tr("MCP3201 CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI, SPI1_MISO},
        {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 153, 120);"}},

        {MCP3202_CS,     tr("MCP3202 CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI, SPI1_MISO},
        {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 153, 120);"}},

        {MCP3204_CS,     tr("MCP3204 CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI, SPI1_MISO},
        {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 153, 120);"}},

        {MCP3208_CS,     tr("MCP3208 CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI, SPI1_MISO},
        {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 153, 120);"}},

        {MLX90393_CS,    tr("MLX90393 CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI, SPI1_MISO},
        {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 153, 120);"}},

        {AS5048A_CS,    tr("AS5048A CS"),
        {ALL},
        {SPI1_SCK, SPI1_MOSI, SPI1_MISO},
        {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 153, 120);"}},

        {LED_SINGLE,     tr("LED Single"),
        {ALL},
        {},
        {}, {"color: rgb(155, 0, 200);"}},

        {LED_ROW,        tr("LED Row"),
        {ALL},
        {},
        {}, {"color: rgb(155, 0, 120);"}},

        {LED_COLUMN,     tr("LED Column"),
        {ALL},
        {},
        {}, {"color: rgb(190, 20, 120);"}},

        {LED_PWM,        tr("LED PWM"),
        {PA_8, PB_0, PB_1, PB_4},
        {},
        {}, {"color: rgb(200, 0, 180);"}},

        {AXIS_ANALOG,    tr("Axis Analog"),
        {ANALOG_IN},
        {},
        {}, {"color: rgb(0, 155, 0);"}},

        {FAST_ENCODER,   tr("Fast Encoder"),
        {PA_8, PA_9},
        {},
        {}, {"color: rgb(200, 10, 10);"}},

        {SPI_SCK,        tr("SPI SCK"),
        {SPI1_SCK},
        {},
        {}, {}},

        {SPI_MOSI,       tr("SPI MOSI"),
        {SPI1_MOSI},
        {},
        {}, {}},

        {SPI_MISO,       tr("SPI MISO"),
        {SPI1_MISO},
        {},
        {}, {}},

        {TLE5011_GEN,    tr("TLE5011 GEN"),
        {PB_6},
        {},
        {}, {}},

        {I2C_SCL,        tr("I2C SCL"),
        {I2C2_SCL},
        {},
        {I2C_SDA}, {"color: rgb(53, 53, 255);"}},

        {I2C_SDA,        tr("I2C SDA"),
        {I2C2_SDA},
        {},
        {I2C_SCL}, {"color: rgb(53, 53, 255);"}},
    };
};

#endif // PINCOMBOBOX_H
