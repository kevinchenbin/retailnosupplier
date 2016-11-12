inherited frmQryNoteCode1: TfrmQryNoteCode1
  Caption = #26597#35810#21333#21495
  ClientHeight = 425
  ClientWidth = 484
  OnShow = FormShow
  ExplicitWidth = 490
  ExplicitHeight = 453
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 489
    Height = 465
    BevelInner = bvNone
    BevelOuter = bvNone
    Font.Charset = ANSI_CHARSET
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    ParentBackground = False
    ParentFont = False
    ExplicitWidth = 489
    ExplicitHeight = 465
    DesignSize = (
      489
      465)
    inherited btnOk: TRzButton
      Left = 191
      Top = 440
      ExplicitLeft = 191
      ExplicitTop = 440
    end
    inherited btnCancel: TRzButton
      Left = 272
      Top = 440
      ExplicitLeft = 272
      ExplicitTop = 440
    end
    object dtedtDate: TRzDateTimeEdit
      Left = 87
      Top = 42
      Width = 120
      Height = 25
      EditType = etDate
      TabOrder = 2
      OnChange = dtedtDateChange
    end
    object spedtID: TRzSpinEdit
      Left = 204
      Top = 42
      Width = 51
      Height = 25
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 3
      OnChange = spedtIDChange
    end
    object edtCode: TRzEdit
      Left = 251
      Top = 42
      Width = 192
      Height = 25
      ReadOnly = True
      ReadOnlyColor = clWindow
      TabOrder = 4
      OnChange = edtCodeChange
    end
    object cbselect: TRzComboBox
      Left = 140
      Top = 71
      Width = 303
      Height = 25
      DisabledColor = clWhite
      ItemHeight = 17
      TabOrder = 5
      OnChange = cbselectChange
    end
    object edtQryVendor: TRzEdit
      Left = 86
      Top = 71
      Width = 54
      Height = 25
      DisabledColor = clWhite
      TabOrder = 6
      OnKeyPress = edtQryVendorKeyPress
    end
    object ch1: TCheckBox
      Left = 16
      Top = 72
      Width = 59
      Height = 19
      Caption = #20379#24212#21830
      TabOrder = 7
    end
    object chstart: TCheckBox
      Left = 16
      Top = 15
      Width = 73
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 8
    end
    object dtpstart: TDateTimePicker
      Left = 88
      Top = 11
      Width = 106
      Height = 25
      Date = 40432.409794375000000000
      Time = 40432.409794375000000000
      TabOrder = 9
      OnChange = dtpstartChange
    end
    object chend: TCheckBox
      Left = 255
      Top = 15
      Width = 73
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 10
    end
    object dtpend: TDateTimePicker
      Left = 333
      Top = 12
      Width = 106
      Height = 25
      Date = 40432.409794375000000000
      Time = 40432.409794375000000000
      TabOrder = 11
      OnChange = dtpendChange
    end
    object chcode: TCheckBox
      Left = 16
      Top = 44
      Width = 49
      Height = 17
      Caption = #21333#21495
      TabOrder = 12
    end
    object DBGrid1: TDBGrid
      Left = 8
      Top = 127
      Width = 465
      Height = 289
      Ctl3D = True
      DataSource = ds
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 13
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      OnKeyPress = DBGrid1KeyPress
      Columns = <
        item
          Expanded = False
          FieldName = 'custmername'
          Title.Alignment = taCenter
          Title.Caption = #20379#24212#21830#21517#31216
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'MoneyCode'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#21333#21495
          Width = 98
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'clearingtype'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#31867#22411
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'clearingstyle'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#26041#24335
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#26085#26399
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'state'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#29366#24577
          Width = 59
          Visible = True
        end>
    end
    object RzButton1: TRzButton
      Left = 312
      Top = 99
      Caption = #26597#35810
      TabOrder = 14
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 397
      Top = 99
      Caption = #21462#28040
      TabOrder = 15
      OnClick = RzButton2Click
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 264
    Top = 232
  end
  object query: TADOQuery
    Parameters = <>
    Left = 280
    Top = 168
  end
  object fcon: TADOConnection
    Left = 352
    Top = 168
  end
end
