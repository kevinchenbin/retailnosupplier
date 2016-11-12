object frmsyspwdchange: Tfrmsyspwdchange
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #36827#20837#31995#32479#35774#32622#23494#30721#20462#25913
  ClientHeight = 178
  ClientWidth = 278
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 17
  object Label1: TLabel
    Left = 32
    Top = 24
    Width = 56
    Height = 17
    Caption = #26087' '#23494' '#30721#65306
  end
  object Label2: TLabel
    Left = 32
    Top = 56
    Width = 56
    Height = 17
    Caption = #26032' '#23494' '#30721#65306
  end
  object Label3: TLabel
    Left = 32
    Top = 89
    Width = 60
    Height = 17
    Caption = #30830#35748#23494#30721#65306
  end
  object edoldpwd: TEdit
    Left = 104
    Top = 21
    Width = 121
    Height = 25
    PasswordChar = '*'
    TabOrder = 0
  end
  object ednewpwd: TEdit
    Left = 104
    Top = 53
    Width = 121
    Height = 25
    PasswordChar = '*'
    TabOrder = 1
  end
  object edpwdagain: TEdit
    Left = 104
    Top = 86
    Width = 121
    Height = 25
    PasswordChar = '*'
    TabOrder = 2
  end
  object btOK: TButton
    Left = 64
    Top = 128
    Width = 75
    Height = 25
    Caption = #30830#23450
    ParentShowHint = False
    ShowHint = False
    TabOrder = 3
    OnClick = btOKClick
  end
  object btConcel: TButton
    Left = 160
    Top = 128
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 4
    OnClick = btConcelClick
  end
  object fcon: TADOConnection
    Left = 264
    Top = 72
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 256
    Top = 16
  end
end
