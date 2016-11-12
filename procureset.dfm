object frmprocureset: Tfrmprocureset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #37319#36141#19994#21153#25511#21046
  ClientHeight = 170
  ClientWidth = 205
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 17
  object sbcancel: TSpeedButton
    Left = 101
    Top = 129
    Width = 77
    Height = 33
    Caption = #21462#28040
    OnClick = sbcancelClick
  end
  object sbok: TSpeedButton
    Left = 14
    Top = 129
    Width = 77
    Height = 33
    Caption = #30830#23450
    OnClick = sbokClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 185
    Height = 111
    TabOrder = 0
    object Label1: TLabel
      Left = 11
      Top = 80
      Width = 96
      Height = 17
      Caption = #39044#35745#21040#36135#40664#35748#22825#25968
    end
    object chprocurefindpwd: TCheckBox
      Left = 11
      Top = 14
      Width = 137
      Height = 17
      Caption = #21551#29992#37319#36141#21333#26597#21333#23494#30721
      TabOrder = 0
    end
    object chprocuredeletepwd: TCheckBox
      Left = 11
      Top = 45
      Width = 157
      Height = 17
      Caption = #21551#29992#37319#36141#21333#21024#34892#23494#30721
      TabOrder = 1
    end
    object chznprocurefindpwd: TCheckBox
      Left = 251
      Top = 117
      Width = 154
      Height = 17
      Caption = #21551#29992#26234#33021#37319#36141#21333#26597#21333#23494#30721
      TabOrder = 2
      Visible = False
    end
    object chznprocuredeletepwd: TCheckBox
      Left = 251
      Top = 151
      Width = 157
      Height = 17
      Caption = #21551#29992#26234#33021#37319#36141#21333#21024#34892#23494#30721
      TabOrder = 3
      Visible = False
    end
    object edday: TEdit
      Left = 112
      Top = 78
      Width = 50
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 4
      Text = '0'
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 624
    Top = 296
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 72
    Top = 488
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 8
    Top = 480
  end
end
