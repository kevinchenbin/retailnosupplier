object frmOrderdetail: TfrmOrderdetail
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35813#20070#35746#21333#26126#32454
  ClientHeight = 452
  ClientWidth = 981
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
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 981
    Height = 417
    Align = alTop
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'clientName'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #23458#25143
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'OrderNtCode'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #21333#21495
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'HdTime'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #35746#21333#26085#26399
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'xiaoqu'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #26657#21306
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'xueyuan'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #23398#38498
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'incode'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20869#37096#35782#21035#30721
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'ISBN'
        Title.Alignment = taCenter
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'bookname'
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'AbbreviatedName'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#31038
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Amount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #25968#37327
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Discount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #25240#25187
        Width = 45
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'SendAmount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #24050#21457
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'UnsendAmount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #26410#21457
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'localnum'
        Title.Alignment = taCenter
        Title.Caption = #38145#23450#25968
        Width = 45
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'usableamount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #21487#29992#25968
        Width = 45
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
        FieldName = 'state'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #29366#24577
        Width = 50
        Visible = True
      end>
  end
  object RzButton1: TRzButton
    Left = 898
    Top = 422
    Caption = #30830#23450
    TabOrder = 1
    OnClick = RzButton1Click
  end
  object ds: TDataSource
    DataSet = aq
    Left = 472
    Top = 184
  end
  object aq: TADOQuery
    LockType = ltBatchOptimistic
    Parameters = <>
    Left = 296
    Top = 216
  end
  object fcon: TADOConnection
    Left = 768
    Top = 184
  end
end
