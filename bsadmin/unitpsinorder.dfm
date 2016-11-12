object frmpsinorder: Tfrmpsinorder
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35746#21333#31579#36873
  ClientHeight = 546
  ClientWidth = 738
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
  object DBGrid1: TDBGrid
    Left = 0
    Top = 123
    Width = 738
    Height = 423
    Align = alBottom
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'OrderNtCode'
        Title.Alignment = taCenter
        Title.Caption = #35746#21333#21495
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ClientName'
        Title.Alignment = taCenter
        Title.Caption = #24215#21517
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'HdTime'
        Title.Alignment = taCenter
        Title.Caption = #35746#21333#26085#26399
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'isbn'
        Title.Alignment = taCenter
        Title.Caption = 'ISBN'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name'
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'price'
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'AbbreviatedName'
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#31038
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'amount'
        Title.Alignment = taCenter
        Title.Caption = #25968#37327
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'UnsendAmount'
        Title.Alignment = taCenter
        Title.Caption = #26410#21457
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'stkamount'
        Title.Alignment = taCenter
        Title.Caption = #24211#23384
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'suppliername'
        Title.Alignment = taCenter
        Title.Caption = #20379#24212#21830
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'discount'
        Title.Alignment = taCenter
        Title.Caption = #25240#25187
        Width = 45
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'author'
        Title.Alignment = taCenter
        Title.Caption = #20316#32773
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'presscount'
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'usableamount'
        Title.Alignment = taCenter
        Title.Caption = #21487#29992#24211#23384#25968
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'Remarks'
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Width = 150
        Visible = True
      end>
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 738
    Height = 121
    Align = alTop
    Caption = #26597#35810#26465#20214
    TabOrder = 1
    object spselectClient: TSpeedButton
      Left = 465
      Top = 53
      Width = 23
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
      OnClick = spselectClientClick
    end
    object chordercode: TCheckBox
      Left = 19
      Top = 24
      Width = 62
      Height = 17
      Caption = #35746#21333#21495
      TabOrder = 0
    end
    object edordercode: TEdit
      Left = 319
      Top = 22
      Width = 144
      Height = 25
      MaxLength = 15
      NumbersOnly = True
      TabOrder = 1
      OnChange = edordercodeChange
    end
    object chclient: TCheckBox
      Left = 19
      Top = 56
      Width = 49
      Height = 17
      Caption = #23458#25143
      TabOrder = 2
    end
    object edclient: TEdit
      Left = 79
      Top = 53
      Width = 56
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 3
      OnKeyPress = edclientKeyPress
    end
    object edtclient: TEdit
      Left = 134
      Top = 53
      Width = 329
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 4
      OnChange = edtclientChange
    end
    object RzButton1: TRzButton
      Left = 632
      Top = 83
      Caption = #26597#35810
      TabOrder = 5
      OnClick = RzButton1Click
    end
    object chstart: TCheckBox
      Left = 19
      Top = 88
      Width = 97
      Height = 17
      Caption = #35746#21333#36215#22987#26102#38388
      TabOrder = 6
    end
    object dtpstart: TDateTimePicker
      Left = 122
      Top = 86
      Width = 102
      Height = 25
      Date = 40306.536538437500000000
      Time = 40306.536538437500000000
      TabOrder = 7
      OnChange = dtpstartChange
    end
    object chend: TCheckBox
      Left = 264
      Top = 89
      Width = 94
      Height = 17
      Caption = #35746#21333#32467#26463#26102#38388
      TabOrder = 8
    end
    object dtpend: TDateTimePicker
      Left = 364
      Top = 86
      Width = 99
      Height = 25
      Date = 40306.536538437500000000
      Time = 40306.536538437500000000
      TabOrder = 9
      OnChange = dtpendChange
    end
    object dtedtDate: TRzDateTimeEdit
      Left = 129
      Top = 22
      Width = 142
      Height = 25
      EditType = etDate
      TabOrder = 10
      OnChange = dtedtDateChange
    end
    object spedtID: TRzSpinEdit
      Left = 270
      Top = 22
      Width = 51
      Height = 25
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 11
      OnChange = spedtIDChange
    end
    object spstgid: TRzSpinEdit
      Left = 79
      Top = 22
      Width = 51
      Height = 25
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 12
      OnChange = spedtIDChange
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 664
    Top = 264
  end
  object query: TADOQuery
    Parameters = <>
    Left = 704
    Top = 256
  end
  object con: TADOConnection
    Left = 600
    Top = 256
  end
  object ds2: TDataSource
    DataSet = query2
    Left = 496
    Top = 400
  end
  object query2: TADOQuery
    Parameters = <>
    Left = 576
    Top = 400
  end
end
