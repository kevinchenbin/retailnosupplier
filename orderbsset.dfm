object frmorderbsset: Tfrmorderbsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #35746#21333#19994#21153#25511#21046
  ClientHeight = 218
  ClientWidth = 358
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
    Left = 217
    Top = 173
    Width = 105
    Height = 33
    Caption = #21462#28040
    OnClick = sbcancelClick
  end
  object sbok: TSpeedButton
    Left = 102
    Top = 173
    Width = 98
    Height = 33
    Caption = #30830#23450
    OnClick = sbokClick
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 8
    Width = 337
    Height = 156
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 0
    object Label1: TLabel
      Left = 164
      Top = 21
      Width = 96
      Height = 17
      Caption = #39044#35745#21457#36135#40664#35748#22825#25968
    end
    object Label2: TLabel
      Left = 164
      Top = 54
      Width = 84
      Height = 17
      Caption = #25552#31034#26102#38388#20026#26368#36817
    end
    object Label3: TLabel
      Left = 310
      Top = 54
      Width = 12
      Height = 17
      Caption = #26376
    end
    object cbautolocalstockbyOrder: TCheckBox
      Left = 16
      Top = 20
      Width = 129
      Height = 18
      Caption = #33258#21160#38145#23450#24211#23384#37327
      TabOrder = 0
    end
    object edday: TEdit
      Left = 268
      Top = 19
      Width = 50
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 1
      Text = '0'
    end
    object chlastorderdiscount: TCheckBox
      Left = 16
      Top = 123
      Width = 137
      Height = 18
      Caption = #36319#36394#19978#27425#35746#36135#25240#25187
      TabOrder = 2
    end
    object chchongfuordertishi: TCheckBox
      Left = 16
      Top = 53
      Width = 129
      Height = 18
      BiDiMode = bdLeftToRight
      Caption = #35746#21333#37325#22797#35760#24405#25552#31034
      ParentBiDiMode = False
      TabOrder = 3
    end
    object edmonth: TEdit
      Left = 254
      Top = 52
      Width = 50
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 4
      Text = '0'
    end
    object chorderfind: TCheckBox
      Left = 16
      Top = 88
      Width = 129
      Height = 18
      BiDiMode = bdLeftToRight
      Caption = #35746#21333#26597#21333#23494#30721#21551#29992
      ParentBiDiMode = False
      TabOrder = 5
    end
    object chorderchange: TCheckBox
      Left = 164
      Top = 88
      Width = 153
      Height = 18
      BiDiMode = bdLeftToRight
      Caption = #35746#21333#20462#25913#21333#22836#23494#30721#21551#29992
      ParentBiDiMode = False
      TabOrder = 6
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
