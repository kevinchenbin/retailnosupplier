object frminorder: Tfrminorder
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #35746#21333#31579#36873
  ClientHeight = 583
  ClientWidth = 915
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 16
  object DBGrid1: TDBGrid
    Left = 0
    Top = 110
    Width = 915
    Height = 428
    Align = alTop
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentFont = False
    PopupMenu = pm
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnTitleClick = DBGrid1TitleClick
    Columns = <
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
        FieldName = 'author'
        Title.Alignment = taCenter
        Title.Caption = #20316#32773
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
        FieldName = 'presscount'
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Width = 35
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
        FieldName = 'discount'
        Title.Alignment = taCenter
        Title.Caption = #25240#25187'%'
        Width = 45
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
        FieldName = 'usableamount'
        Title.Alignment = taCenter
        Title.Caption = #21487#29992#25968
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Orderstr'
        Title.Alignment = taCenter
        Title.Caption = #35746#21333#21495
        Width = 100
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
        FieldName = 'ClientName'
        Title.Alignment = taCenter
        Title.Caption = #23458#25143#21517#31216
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Remarks'
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'OID'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'DetailID'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'needprocurenum'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'Orderstr'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'Bkcatalogid'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'FullName'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'ClientID'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'OrderNtCode'
        Visible = False
      end>
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 915
    Height = 110
    Align = alTop
    Caption = #26597#35810#26465#20214
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    ExplicitLeft = -8
    object spselectClient: TSpeedButton
      Left = 632
      Top = 50
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
    object Label1: TLabel
      Left = 670
      Top = 24
      Width = 36
      Height = 17
      Caption = #20379#24212#21830
    end
    object chordercode: TCheckBox
      Left = 19
      Top = 26
      Width = 62
      Height = 17
      Caption = #35746#21333#21495
      TabOrder = 0
    end
    object edordercode: TEdit
      Left = 271
      Top = 22
      Width = 362
      Height = 25
      MaxLength = 15
      NumbersOnly = True
      TabOrder = 13
      Visible = False
      OnChange = edordercodeChange
    end
    object chclient: TCheckBox
      Left = 19
      Top = 53
      Width = 49
      Height = 17
      Caption = #23458#25143
      TabOrder = 2
    end
    object edclient: TEdit
      Left = 79
      Top = 50
      Width = 56
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 3
      OnKeyPress = edclientKeyPress
    end
    object edtclient: TEdit
      Left = 134
      Top = 50
      Width = 499
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 4
      OnChange = edtclientChange
    end
    object RzButton1: TRzButton
      Left = 712
      Top = 77
      Width = 81
      Height = 27
      Caption = #26597#35810
      TabOrder = 11
      OnClick = RzButton1Click
    end
    object chstart: TCheckBox
      Left = 19
      Top = 80
      Width = 97
      Height = 17
      Caption = #35746#21333#36215#22987#26102#38388
      TabOrder = 5
    end
    object dtpstart: TDateTimePicker
      Left = 122
      Top = 77
      Width = 102
      Height = 25
      Date = 40306.536538437500000000
      Time = 40306.536538437500000000
      TabOrder = 6
      OnChange = dtpstartChange
    end
    object chend: TCheckBox
      Left = 264
      Top = 80
      Width = 94
      Height = 17
      Caption = #35746#21333#32467#26463#26102#38388
      TabOrder = 7
    end
    object dtpend: TDateTimePicker
      Left = 364
      Top = 77
      Width = 99
      Height = 25
      Date = 40306.536538437500000000
      Time = 40306.536538437500000000
      TabOrder = 8
      OnChange = dtpendChange
    end
    object dtedtDate: TRzDateTimeEdit
      Left = 79
      Top = 22
      Width = 145
      Height = 25
      EditType = etDate
      TabOrder = 14
      Visible = False
      OnChange = dtedtDateChange
    end
    object spedtID: TRzSpinEdit
      Left = 222
      Top = 22
      Width = 51
      Height = 25
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 15
      Visible = False
      OnChange = spedtIDChange
    end
    object sbcaigou: TRzButton
      Left = 808
      Top = 78
      Width = 81
      Height = 26
      Caption = #29983#25104#37319#36141#21333
      TabOrder = 12
      OnClick = sbcaigouClick
    end
    object cbordertype: TComboBox
      Left = 534
      Top = 78
      Width = 99
      Height = 25
      ItemHeight = 17
      ItemIndex = 0
      TabOrder = 10
      Text = #20840#37096
      Items.Strings = (
        #20840#37096
        #20869#37096#35746#21333
        #23458#25143#35746#21333)
    end
    object cbordercheck: TCheckBox
      Left = 466
      Top = 82
      Width = 68
      Height = 17
      Caption = #35746#21333#31867#22411
      TabOrder = 9
    end
    object editdanhao: TEdit
      Left = 79
      Top = 22
      Width = 554
      Height = 23
      Ctl3D = False
      NumbersOnly = True
      ParentCtl3D = False
      TabOrder = 1
    end
    object Edit1: TEdit
      Left = 712
      Top = 22
      Width = 57
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 16
      OnKeyPress = edclientKeyPress
    end
    object cbsupplier: TComboBox
      Left = 766
      Top = 22
      Width = 146
      Height = 25
      ItemHeight = 17
      ItemIndex = 0
      TabOrder = 17
      Text = #20840#37096
      Items.Strings = (
        #20840#37096
        #20869#37096#35746#21333
        #23458#25143#35746#21333)
    end
  end
  object RzButton3: TRzButton
    Left = 321
    Top = 544
    Width = 167
    Caption = #28155#21152#21040#19968#33324#37319#36141#21333
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Visible = False
    OnClick = RzButton3Click
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
  object pm: TPopupMenu
    Left = 352
    Top = 280
    object N1: TMenuItem
      Caption = #20840#36873
      OnClick = N1Click
    end
  end
  object cmdAddNote: TADOCommand
    CommandText = 'USP_BS_OrderToCaigou;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@return_value'
        DataType = ftInteger
        Direction = pdReturnValue
        Size = 10
        Value = Null
      end
      item
        Name = '@OperatorID'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@StgID'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@CODEMODE'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@groupid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@ReturnCode'
        DataType = ftString
        Direction = pdOutput
        Size = 1000
        Value = Null
      end
      item
        Name = '@ReturnCodeint'
        DataType = ftString
        Direction = pdOutput
        Size = 1000
        Value = Null
      end
      item
        Name = '@Returnint'
        DataType = ftInteger
        Direction = pdOutput
        Size = 10
        Value = Null
      end>
    Left = 408
    Top = 193
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 528
    Top = 192
  end
end
