object frmaddclient: Tfrmaddclient
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #28155#21152#23458#25143
  ClientHeight = 111
  ClientWidth = 334
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 6
    Top = 31
    Width = 24
    Height = 17
    Caption = #23458#25143
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object edclient: TEdit
    Left = 43
    Top = 27
    Width = 73
    Height = 25
    AutoSize = False
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    OnKeyPress = edclientKeyPress
  end
  object cbclient: TComboBox
    Left = 115
    Top = 27
    Width = 206
    Height = 25
    BevelKind = bkFlat
    Style = csDropDownList
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ItemHeight = 17
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 1
    OnKeyPress = cbclientKeyPress
  end
  object Button1: TButton
    Left = 169
    Top = 72
    Width = 75
    Height = 25
    Caption = #30830#23450
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ModalResult = 1
    ParentFont = False
    TabOrder = 2
  end
  object Button2: TButton
    Left = 250
    Top = 72
    Width = 75
    Height = 25
    Caption = #21462#28040
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ModalResult = 2
    ParentFont = False
    TabOrder = 3
  end
  object ADOConnection1: TADOConnection
    Left = 112
    Top = 72
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 24
    Top = 64
  end
end
