object frminputmessage: Tfrminputmessage
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  ClientHeight = 168
  ClientWidth = 348
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
    Left = 16
    Top = 8
    Width = 38
    Height = 17
    Caption = 'Label1'
  end
  object meminfor: TMemo
    Left = 48
    Top = 31
    Width = 268
    Height = 83
    TabOrder = 0
    OnKeyPress = meminforKeyPress
  end
  object Button1: TButton
    Left = 160
    Top = 135
    Width = 75
    Height = 25
    Caption = #30830#23450'(&S)'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object Button2: TButton
    Left = 241
    Top = 135
    Width = 75
    Height = 25
    Caption = #21462#28040'(&C)'
    ModalResult = 2
    TabOrder = 2
  end
end
