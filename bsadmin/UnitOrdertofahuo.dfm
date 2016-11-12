object frmOrdertoFahuo: TfrmOrdertoFahuo
  Left = 0
  Top = 0
  Caption = #35746#21333#31579#36873
  ClientHeight = 573
  ClientWidth = 743
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 743
    Height = 573
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 6
      Top = 11
      Width = 723
      Height = 134
      Caption = #26597#35810#26465#20214
      TabOrder = 0
      object chordercode: TCheckBox
        Left = 19
        Top = 24
        Width = 62
        Height = 17
        Caption = #35746#21333#21495
        TabOrder = 0
      end
      object edordercode: TEdit
        Left = 271
        Top = 22
        Width = 192
        Height = 21
        MaxLength = 15
        NumbersOnly = True
        TabOrder = 1
        OnChange = edordercodeChange
      end
      object chclient: TCheckBox
        Left = 19
        Top = 51
        Width = 49
        Height = 17
        Caption = #23458#25143
        TabOrder = 2
      end
      object edclient: TEdit
        Left = 79
        Top = 49
        Width = 56
        Height = 21
        TabOrder = 3
        OnKeyPress = edclientKeyPress
      end
      object RzButton1: TRzButton
        Left = 607
        Top = 101
        Caption = #26597#35810
        TabOrder = 4
        OnClick = RzButton1Click
      end
      object chxiaoqu: TCheckBox
        Left = 19
        Top = 76
        Width = 49
        Height = 17
        Caption = #26657#21306
        TabOrder = 5
      end
      object cbxiaoqu: TComboBox
        Left = 79
        Top = 74
        Width = 145
        Height = 21
        ItemHeight = 0
        TabOrder = 6
        OnChange = cbxiaoquChange
      end
      object chxueyuan: TCheckBox
        Left = 264
        Top = 76
        Width = 49
        Height = 17
        Caption = #23398#38498
        TabOrder = 7
      end
      object cbxueyuan: TComboBox
        Left = 318
        Top = 74
        Width = 145
        Height = 21
        ItemHeight = 0
        TabOrder = 8
        OnChange = cbxueyuanChange
      end
      object chclass: TCheckBox
        Left = 492
        Top = 76
        Width = 49
        Height = 17
        Caption = #29677#32423
        TabOrder = 9
      end
      object cbclass: TComboBox
        Left = 538
        Top = 74
        Width = 145
        Height = 21
        ItemHeight = 0
        TabOrder = 10
        OnChange = cbclassChange
      end
      object chstart: TCheckBox
        Left = 19
        Top = 102
        Width = 97
        Height = 17
        Caption = #35746#21333#36215#22987#26102#38388
        TabOrder = 11
      end
      object dtpstart: TDateTimePicker
        Left = 122
        Top = 100
        Width = 102
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 12
        OnChange = dtpstartChange
      end
      object chend: TCheckBox
        Left = 264
        Top = 103
        Width = 94
        Height = 17
        Caption = #35746#21333#32467#26463#26102#38388
        TabOrder = 13
      end
      object dtpend: TDateTimePicker
        Left = 364
        Top = 100
        Width = 99
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 14
        OnChange = dtpendChange
      end
      object dtedtDate: TRzDateTimeEdit
        Left = 79
        Top = 22
        Width = 145
        Height = 21
        EditType = etDate
        TabOrder = 15
        OnChange = dtedtDateChange
      end
      object spedtID: TRzSpinEdit
        Left = 222
        Top = 22
        Width = 51
        Height = 21
        AllowKeyEdit = True
        Max = 99999.000000000000000000
        TabOrder = 16
        OnChange = spedtIDChange
      end
      object cbclient: TComboBox
        Left = 137
        Top = 49
        Width = 326
        Height = 21
        ItemHeight = 0
        TabOrder = 17
        OnChange = cbclientChange
        OnClick = cbclientClick
        OnKeyPress = cbclientKeyPress
      end
    end
    object DBGrid1: TDBGrid
      Left = 6
      Top = 151
      Width = 723
      Height = 386
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
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
          Title.Caption = #23458#25143
          Width = 141
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #35746#21333#26085#26399
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'xiaoqu'
          Title.Alignment = taCenter
          Title.Caption = #26657#21306
          Width = 58
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'xueyuan'
          Title.Alignment = taCenter
          Title.Caption = #23398#38498
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'class'
          Title.Alignment = taCenter
          Title.Caption = #29677#32423
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'isbn'
          Title.Alignment = taCenter
          Title.Caption = 'ISBN'
          Width = 58
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 96
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stkamount'
          Title.Alignment = taCenter
          Title.Caption = #24211#23384#25968#37327
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'incode'
          Title.Alignment = taCenter
          Title.Caption = #20869#37096#35782#21035#30721
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 204
          Visible = True
        end>
    end
    object RzButton3: TRzButton
      Left = 622
      Top = 543
      Width = 107
      Caption = #30830#23450#21457#36135#35746#21333
      TabOrder = 2
      OnClick = RzButton3Click
    end
    object chall: TCheckBox
      Left = 486
      Top = 114
      Width = 121
      Height = 17
      Caption = #21482#26597#35810#26377#24211#23384#30340
      TabOrder = 3
    end
    object RzButton2: TRzButton
      Left = 486
      Top = 543
      Width = 107
      Caption = #28155#21152#21040#39044#21457#21333
      TabOrder = 4
      OnClick = RzButton2Click
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
