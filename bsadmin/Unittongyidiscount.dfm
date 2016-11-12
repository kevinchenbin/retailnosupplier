object frmtongyidiscount: Tfrmtongyidiscount
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #32479#19968#25240#25187
  ClientHeight = 162
  ClientWidth = 260
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 17
  object Label1: TLabel
    Left = 44
    Top = 35
    Width = 4
    Height = 17
  end
  object nedit: TRzNumericEdit
    Left = 101
    Top = 32
    Width = 151
    Height = 25
    TabOrder = 0
    IntegersOnly = False
    DisplayFormat = '##0.00'
  end
  object sbok: TRzButton
    Left = 76
    Top = 121
    Default = True
    ModalResult = 1
    Caption = #30830#23450
    TabOrder = 1
  end
  object sbcancel: TRzButton
    Left = 169
    Top = 121
    Cancel = True
    ModalResult = 2
    Caption = #21462#28040
    TabOrder = 2
  end
  object cbfahuofangshi: TComboBox
    Left = 101
    Top = 77
    Width = 151
    Height = 25
    Style = csDropDownList
    ItemHeight = 17
    ItemIndex = 0
    TabOrder = 3
    Text = #31038#30452#21457
    Items.Strings = (
      #31038#30452#21457
      #28100#36716#21457)
  end
  object CheckBox1: TCheckBox
    Left = 24
    Top = 36
    Width = 71
    Height = 17
    Caption = #32479#19968#25240#25187':'
    TabOrder = 4
  end
  object CheckBox2: TCheckBox
    Left = 24
    Top = 80
    Width = 71
    Height = 17
    Caption = #21457#36135#26041#24335':'
    TabOrder = 5
  end
end
