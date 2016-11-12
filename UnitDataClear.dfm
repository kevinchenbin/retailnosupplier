object Form2: TForm2
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #25968#25454#25972#29702
  ClientHeight = 622
  ClientWidth = 898
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 20
  object Label1: TLabel
    Left = 16
    Top = 29
    Width = 31
    Height = 20
    Caption = #24215#21495':'
  end
  object Label2: TLabel
    Left = 176
    Top = 29
    Width = 31
    Height = 20
    Caption = #31867#21035':'
  end
  object Label3: TLabel
    Left = 329
    Top = 29
    Width = 59
    Height = 20
    Caption = #36215#22987#26102#38388':'
  end
  object Label4: TLabel
    Left = 517
    Top = 29
    Width = 59
    Height = 20
    Caption = #32467#26463#26102#38388':'
  end
  object sb: TSpeedButton
    Left = 704
    Top = 24
    Width = 65
    Height = 30
    Caption = #26597#35810
  end
  object cbstg: TComboBox
    Left = 53
    Top = 26
    Width = 110
    Height = 28
    ItemHeight = 20
    TabOrder = 0
  end
  object cbpx: TComboBox
    Left = 213
    Top = 26
    Width = 110
    Height = 28
    ItemHeight = 20
    ItemIndex = 0
    TabOrder = 1
    Text = #38646#21806
    OnChange = cbpxChange
    Items.Strings = (
      #38646#21806
      #25209#38144)
  end
  object DateTimePicker1: TDateTimePicker
    Left = 394
    Top = 26
    Width = 110
    Height = 28
    Date = 41621.430951122680000000
    Time = 41621.430951122680000000
    TabOrder = 2
  end
  object DateTimePicker2: TDateTimePicker
    Left = 582
    Top = 26
    Width = 110
    Height = 28
    Date = 41621.430951122680000000
    Time = 41621.430951122680000000
    TabOrder = 3
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 80
    Width = 761
    Height = 257
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 4
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -14
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #24207
        Width = 30
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #21333#21495
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #23458#25143#21517#31216
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #26085#26399
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #30721#27915
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #23454#27915
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #25805#20316#21592
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Width = 120
        Visible = True
      end>
  end
  object DBGrid2: TDBGrid
    Left = 8
    Top = 128
    Width = 761
    Height = 345
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 5
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -14
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #24207
        Width = 30
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #21333#21495
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #20250#21592#21517#31216
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #20250#21592#21345#21495
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #26085#26399
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #25968#37327
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #30721#27915
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #23454#27915
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        Title.Alignment = taCenter
        Title.Caption = #25805#20316#21592
        Width = 120
        Visible = True
      end>
  end
  object DataSource1: TDataSource
    Left = 384
    Top = 192
  end
  object DataSource2: TDataSource
    Left = 472
    Top = 216
  end
  object ADOQuery1: TADOQuery
    Parameters = <>
    Left = 240
    Top = 336
  end
  object ADOQuery2: TADOQuery
    Parameters = <>
    Left = 288
    Top = 200
  end
end
