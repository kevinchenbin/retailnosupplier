object frmdiaoboset: Tfrmdiaoboset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #37197#36865#19994#21153#25511#21046
  ClientHeight = 208
  ClientWidth = 355
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
  object Label3: TLabel
    Left = 173
    Top = 12
    Width = 11
    Height = 17
    Caption = '%'
  end
  object Label1: TLabel
    Left = 17
    Top = 12
    Width = 96
    Height = 17
    Caption = #26368#36817#20837#24211#25240#25187#21152#28857
  end
  object Label2: TLabel
    Left = 221
    Top = 12
    Width = 48
    Height = 17
    Caption = #40664#35748#25240#25187
  end
  object Label4: TLabel
    Left = 330
    Top = 12
    Width = 11
    Height = 17
    Caption = '%'
  end
  object RadioGroup1: TRadioGroup
    Left = 15
    Top = 40
    Width = 320
    Height = 85
    Caption = #37197#36865#25240#25187#35774#32622
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      #20837#24211#24179#22343#25240#25187
      #26368#36817#20837#24211#25240#25187
      #26368#36817#20837#24211#25240#25187#21152#25187
      #40664#35748#25240#25187)
    TabOrder = 0
  end
  object edadddiscount: TEdit
    Left = 119
    Top = 11
    Width = 49
    Height = 23
    Alignment = taRightJustify
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 1
    Text = '100'
    OnKeyPress = edadddiscountKeyPress
  end
  object eddefaultdiscount: TEdit
    Left = 275
    Top = 11
    Width = 49
    Height = 23
    Alignment = taRightJustify
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 2
    Text = '100'
    OnKeyPress = edadddiscountKeyPress
  end
  object RzButton1: TRzButton
    Left = 119
    Top = 163
    Width = 93
    Height = 35
    Caption = #30830#23450
    TabOrder = 3
    OnClick = RzButton1Click
  end
  object RzButton2: TRzButton
    Left = 231
    Top = 163
    Width = 93
    Height = 35
    Caption = #21462#28040
    TabOrder = 4
    OnClick = RzButton2Click
  end
  object chpeisongsametishi: TCheckBox
    Left = 21
    Top = 136
    Width = 132
    Height = 17
    Caption = #37325#22797#24405#20837#25552#37266
    TabOrder = 5
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
