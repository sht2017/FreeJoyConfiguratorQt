#ifndef PINCOMBOBOX_H
#define PINCOMBOBOX_H

#include <QWidget>
#include <QTranslator>
#include <QDebug>

#include "global.h"
#include "deviceconfig.h"

#define PIN_TYPE_COUNT 25
enum        // разделить и вынести отдельно
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


struct cBox         // private:
{
    int device_enum_index;
    QString gui_name;
    int pin_type[10];
    int pin_except[10];
    int interaction[10];
    QString styleSheet;         // стиль взаимодействия
};

struct pins         // private:
{
    int pin;
    QString gui_name;
    int pin_type[10];
};


namespace Ui {
class PinComboBox;
}

class PinComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit PinComboBox(QWidget *parent = nullptr);
    ~PinComboBox();
    int GetIndex();                         // удалить?
    //void SetIndex();
    void ResetPin();
    void SetIndex_Iteraction(int index, int sender_index);
    void InitializationPins(uint pin);
    void ReadFromConfig(uint pin);
    void WriteToConfig(uint pin);

    void RetranslateUi();

    int GetEnumValue();                     // удалить?

    //private?
    QString EnumToString(int deviceEnum);   // удалить?
    int EnumToIndex(int deviceEnum);        // удалить?
    int pin_number_ = -1;
    //! номер элемента в pin_types
    std::vector<int> enum_gui_index;            // rename to pin_types_index
    std::vector<int> enum_index;
    int previous_index_ = 0;

    // public private _
    bool is_call_interaction_ = false;
    bool is_interacts_ = false;
    uint interact_count_ = 0;
    int call_interaction_;
    QString styleSheet_default_;            // убрать из конструктора, настроить для смены стилей

signals:
    void valueChangedForInteraction(int index, int sender_index, int pin);
    void currentIndexChanged(int current_device_enum, int previous_device_enum, int pin_number);
private slots:
    void IndexChanged(int index);

public:     // private?
    pins const pin_list[30] =       // каждый пин хранит по структуре. а жирно не будет?
    {
        {PA_0,  {tr("Pin A0")},     {ANALOG_IN}},   // пин // GUI name // его типы
        {PA_1,  {tr("Pin A1")},     {ANALOG_IN}},   // добавить SERIAL, PWM...
        {PA_2,  {tr("Pin A2")},     {ANALOG_IN}},
        {PA_3,  {tr("Pin A3")},     {ANALOG_IN}},
        {PA_4,  {tr("Pin A4")},     {ANALOG_IN}},
        {PA_5,  {tr("Pin A5")},     {ANALOG_IN}},
        {PA_6,  {tr("Pin A6")},     {ANALOG_IN}},
        {PA_7,  {tr("Pin A7")},     {ANALOG_IN}},
        {PA_8,  {tr("Pin A8")},     {}},
        {PA_9,  {tr("Pin A9")},     {}},
        {PA_10, {tr("Pin A10")},    {}},
        {PA_15, {tr("Pin A15")},    {SPI1_NSS}},
        {PB_0,  {tr("Pin B0")},     {}},
        {PB_1,  {tr("Pin B1")},     {}},
        {PB_3,  {tr("Pin B3")},     {SPI1_SCK}},
        {PB_4,  {tr("Pin B4")},     {SPI1_MISO}},
        {PB_5,  {tr("Pin B5")},     {SPI1_MOSI}},
        {PB_6,  {tr("Pin B6")},     {}},
        {PB_7,  {tr("Pin B7")},     {}},
        {PB_8,  {tr("Pin B8")},     {I2C1_SCL}},
        {PB_9,  {tr("Pin B9")},     {I2C1_SDA}},
        {PB_10, {tr("Pin B10")},    {}},
        {PB_11, {tr("Pin B11")},    {}},
        {PB_12, {tr("Pin B12")},    {}},
        {PB_13, {tr("Pin B13")},    {}},
        {PB_14, {tr("Pin B14")},    {}},
        {PB_15, {tr("Pin B15")},    {}},
        {PC_13, {tr("Pin C13")},    {}},
        {PC_14, {tr("Pin C14")},    {}},
        {PC_15, {tr("Pin C15")},    {}},
    };
    cBox const pin_types[PIN_TYPE_COUNT] =
    {
        {NOT_USED,       tr("Not Used"),
         {ALL},
         {},
         {}, {}},

        {BUTTON_GND,     tr("Button Gnd"),      // контроллер enum,  имя в ui   tr(нужен перевод)
         {ALL},                                 // добавление в конкретный пин или пины типа
         {},                                    // исключая пины
         {}, {"color: rgb(255, 0, 255);"}},     // взаимодействие с другими типами // стиль color, background-color, border-color...

        {BUTTON_VCC,     tr("Button Vcc"),
         {ALL},
         {},
         {}, {}},

        {BUTTON_ROW,     tr("Button Row"),
         {ALL},
         {},
         {}, {}},

        {BUTTON_COLUMN,  tr("Button Column"),
         {ALL},
         {},
         {}, {}},

        {SHIFT_REG_LATCH,tr("ShiftReg LATCH"),
         {ALL},
         {SPI1_SCK},
         {SPI_SCK}, {"color: rgb(0, 153, 0);"}},

        {SHIFT_REG_DATA, tr("ShiftReg DATA"),
         {ALL},
         {SPI1_SCK},
         {SPI_SCK}, {"color: rgb(0, 153, 0);"}},

        {TLE5011_CS,     tr("TLE5011 CS"),
         {ALL},
         {SPI1_SCK, SPI1_MOSI, PB_6},
         {SPI_SCK, SPI_MOSI, TLE5011_GEN}, {"color: rgb(53, 153, 155);"}},

        {MCP3201_CS,     tr("MCP3201 CS"),
         {ALL},
         {SPI1_SCK, SPI1_MOSI, SPI_MISO},
         {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(153, 153, 55);"}},

        {MCP3202_CS,     tr("MCP3202 CS"),
         {ALL},
         {SPI1_SCK, SPI1_MOSI, SPI_MISO},
         {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(153, 53, 155);"}},

        {MCP3204_CS,     tr("MCP3204 CS"),
         {ALL},
         {SPI1_SCK, SPI1_MOSI, SPI_MISO},
         {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 53, 0);"}},

        {MCP3208_CS,     tr("MCP3208 CS"),
         {ALL},
         {SPI1_SCK, SPI1_MOSI, SPI_MISO},
         {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(53, 0, 55);"}},

        {MLX90393_CS,    tr("MLX90393 CS"),
         {ALL},
         {SPI1_SCK, SPI1_MOSI, SPI_MISO},
         {SPI_SCK, SPI_MOSI, SPI_MISO}, {"color: rgb(0, 53, 55);"}},

        {LED_SINGLE,     tr("LED Single"),
         {ALL},
         {},
         {}, {}},

        {LED_ROW,        tr("LED Row"),
         {ALL},
         {},
         {}, {}},

        {LED_COLUMN,     tr("LED Column"),
         {ALL},
         {},
         {}, {}},

        {LED_PWM,        tr("LED PWM"),
         {PB_0, PB_1, PB_4},
         {},
         {}, {}},

        {AXIS_ANALOG,    tr("Axis Analog"),
         {ANALOG_IN},
         {},
         {}, {}},

        {FAST_ENCODER,   tr("Fast Encoder"),
         {PA_8, PA_9},
         {},
         {}, {}},

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
         {I2C1_SCL},
         {},
         {I2C_SDA}, {"color: rgb(53, 53, 255);"}},

        {I2C_SDA,        tr("I2C SDA"),
         {I2C1_SDA},
         {},
         {I2C_SCL}, {"color: rgb(53, 53, 255);"}},

    };


private:
    Ui::PinComboBox *ui;
    int last_deleted_ = 0;              // удалить?
};

#endif // PINCOMBOBOX_H
