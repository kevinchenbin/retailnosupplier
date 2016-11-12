object frmstockalarmbsset: Tfrmstockalarmbsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #24211#23384#39044#35686#25511#21046
  ClientHeight = 208
  ClientWidth = 201
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
    Left = 110
    Top = 166
    Width = 75
    Height = 33
    Caption = #21462#28040
    OnClick = sbcancelClick
  end
  object sbok: TSpeedButton
    Left = 24
    Top = 166
    Width = 75
    Height = 33
    Caption = #30830#23450
    OnClick = sbokClick
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 6
    Width = 177
    Height = 147
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 0
    object Label2: TLabel
      Left = 15
      Top = 115
      Width = 60
      Height = 17
      Caption = #25552#31034#26102#38388#20026
    end
    object Label3: TLabel
      Left = 134
      Top = 115
      Width = 12
      Height = 17
      Caption = #26102
    end
    object chloginstockalarm: TCheckBox
      Left = 16
      Top = 15
      Width = 137
      Height = 18
      Caption = #27599#27425#30331#38470#26102#25552#31034
      TabOrder = 0
    end
    object chkucunstockalarm: TCheckBox
      Left = 16
      Top = 47
      Width = 121
      Height = 18
      BiDiMode = bdLeftToRight
      Caption = #24211#23384#31649#29702#26102#25552#31034
      ParentBiDiMode = False
      TabOrder = 1
    end
    object edtime: TEdit
      Left = 81
      Top = 113
      Width = 50
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 2
      Text = '0'
      OnKeyPress = edtimeKeyPress
    end
    object chtimestockalarm: TCheckBox
      Left = 16
      Top = 79
      Width = 105
      Height = 18
      Caption = #25353#26102#38388#28857#25552#31034
      TabOrder = 3
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 624
    Top = 296
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 488
    Top = 416
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 528
    Top = 368
  end
end
