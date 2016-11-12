object frmQryCode: TfrmQryCode
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #26597#21333
  ClientHeight = 289
  ClientWidth = 286
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
  object ch1: TCheckBox
    Left = 6
    Top = 13
    Width = 75
    Height = 17
    Caption = #36215#22987#26102#38388
    TabOrder = 0
  end
  object ch2: TCheckBox
    Left = 6
    Top = 48
    Width = 75
    Height = 17
    Caption = #32467#26463#26102#38388
    TabOrder = 1
  end
  object dtp1: TDateTimePicker
    Left = 87
    Top = 9
    Width = 97
    Height = 25
    Date = 40924.641244340280000000
    Time = 40924.641244340280000000
    TabOrder = 2
    OnChange = dtp1Change
  end
  object dtp2: TDateTimePicker
    Left = 87
    Top = 44
    Width = 97
    Height = 25
    Date = 40924.641244340280000000
    Time = 40924.641244340280000000
    TabOrder = 3
    OnChange = dtp2Change
  end
  object RzButton1: TRzButton
    Left = 203
    Top = 49
    Caption = #26597#35810
    TabOrder = 4
    OnClick = RzButton1Click
  end
  object DBGrid1: TDBGrid
    Left = 6
    Top = 80
    Width = 275
    Height = 205
    DataSource = ds
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 5
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    OnKeyPress = DBGrid1KeyPress
    Columns = <
      item
        Expanded = False
        FieldName = 'code'
        Title.Alignment = taCenter
        Title.Caption = #21333#21495
        Width = 109
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'hdtime'
        Title.Alignment = taCenter
        Title.Caption = #26085#26399
        Width = 124
        Visible = True
      end>
  end
  object fcon: TADOConnection
    Left = 232
    Top = 65520
  end
  object ds: TDataSource
    DataSet = query
    Left = 168
    Top = 152
  end
  object query: TADOQuery
    Parameters = <>
    Left = 88
    Top = 184
  end
end
