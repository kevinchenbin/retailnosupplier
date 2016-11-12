object frmBookQuery: TfrmBookQuery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #20070#30446#26597#35810
  ClientHeight = 185
  ClientWidth = 448
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 17
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 448
    Height = 145
    Align = alTop
    Caption = #26597#35810#26465#20214
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 404
      Top = 76
      Width = 27
      Height = 23
      Flat = True
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FF00FF00CCCC
        CC00C0C0C000E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCCCC006699
        99006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0066CC
        FF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCC
        FF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00CCCCFF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00CCCCFF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC99
        9900CC999900CC999900CCCC9900E5E5E500FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EA
        BF00FFFFCC00F2EABF00F2EABF00CC999900ECC6D900FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900FFCC9900FFFFCC00FFFF
        CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00CC999900E5E5E500FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFCC00F2EABF00FFFF
        CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00F2EABF00CCCC9900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00CCCC9900FFCC9900F2EABF00F2EABF00FFFF
        CC00FFFFCC00FFFFCC00FFFFFF00FFFFFF00F2EABF00CC999900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00CC999900F2EABF00F2EABF00F2EABF00F2EA
        BF00FFFFCC00FFFFCC00FFFFCC00FFFFCC00FFFFCC00CC999900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00CCCC9900F2EABF00FFFFCC00F2EABF00F2EA
        BF00F2EABF00FFFFCC00FFFFCC00FFFFCC00F2EABF00CC999900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EA
        BF00F2EABF00F2EABF00F2EABF00FFFFCC00CCCC9900CCCC9900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900ECC6D900FFFFFF00FFFF
        CC00F2EABF00F2EABF00F2EABF00FFCC9900CC999900E5E5E500FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FFCCCC00CC999900FFCCCC00F2EA
        BF00F2EABF00F2EABF00CCCC9900CC999900FFCCCC00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00E5E5E500CCCC9900CC99
        9900CC999900CC999900CC999900E5E5E500FF00FF00FF00FF00}
      OnClick = SpeedButton1Click
    end
    object edisbn: TEdit
      Left = 65
      Top = 20
      Width = 133
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 0
      OnChange = edisbnChange
    end
    object chpress: TCheckBox
      Left = 6
      Top = 107
      Width = 57
      Height = 17
      Caption = #20986#29256#31038
      TabOrder = 1
    end
    object cbpress: TComboBox
      Left = 110
      Top = 103
      Width = 88
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 17
      ParentCtl3D = False
      TabOrder = 2
      OnChange = cbpressChange
    end
    object edpress: TEdit
      Left = 65
      Top = 103
      Width = 46
      Height = 25
      AutoSize = False
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 3
      OnKeyPress = edpressKeyPress
    end
    object chtype: TCheckBox
      Left = 213
      Top = 79
      Width = 45
      Height = 17
      Caption = #31867#21035
      TabOrder = 4
    end
    object chisbn: TCheckBox
      Left = 6
      Top = 22
      Width = 43
      Height = 17
      Caption = #20070#21495
      TabOrder = 5
    end
    object edname: TEdit
      Left = 261
      Top = 20
      Width = 142
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 6
      OnChange = ednameChange
    end
    object chname: TCheckBox
      Left = 213
      Top = 22
      Width = 45
      Height = 17
      Caption = #20070#21517
      TabOrder = 7
    end
    object edprice: TEdit
      Left = 65
      Top = 76
      Width = 133
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 8
      OnChange = edpriceChange
    end
    object chprice: TCheckBox
      Left = 6
      Top = 79
      Width = 43
      Height = 17
      Caption = #23450#20215
      TabOrder = 9
    end
    object edauthor: TEdit
      Left = 261
      Top = 48
      Width = 142
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 10
      OnChange = edauthorChange
    end
    object chauthor: TCheckBox
      Left = 213
      Top = 51
      Width = 43
      Height = 17
      Caption = #20316#32773
      TabOrder = 11
    end
    object edtyname: TEdit
      Left = 297
      Top = 76
      Width = 106
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 12
    end
    object edpyquery: TEdit
      Left = 261
      Top = 76
      Width = 37
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 13
      OnKeyPress = edpyqueryKeyPress
    end
  end
  object btOK: TRzButton
    Left = 263
    Top = 151
    Caption = #30830#35748
    ParentColor = True
    TabOrder = 1
    OnClick = btOKClick
  end
  object btConcel: TRzButton
    Left = 356
    Top = 151
    Caption = #21462#28040
    ParentColor = True
    TabOrder = 2
    OnClick = RzButton1Click
  end
  object cbselftcode: TCheckBox
    Left = 6
    Top = 50
    Width = 53
    Height = 17
    Caption = #33258#32534#30721
    TabOrder = 3
  end
  object editselfcode: TEdit
    Left = 64
    Top = 48
    Width = 133
    Height = 23
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 4
    OnChange = editselfcodeChange
  end
  object fcon: TADOConnection
    Left = 344
    Top = 65520
  end
end
