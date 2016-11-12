object frmchangeselect: Tfrmchangeselect
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #26356#25442#25968#30446#36873#25321
  ClientHeight = 377
  ClientWidth = 745
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
    Top = 0
    Width = 745
    Height = 341
    Align = alTop
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    OnKeyDown = DBGrid1KeyDown
    Columns = <
      item
        Expanded = False
        FieldName = 'ISBN'
        Title.Alignment = taCenter
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name'
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Width = 250
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'UserDefCode'
        Title.Alignment = taCenter
        Title.Caption = #33258#32534#30721
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Price'
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Author'
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
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PressCount'
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Width = 50
        Visible = True
      end>
  end
  object btgenhuan: TButton
    Left = 648
    Top = 347
    Width = 97
    Height = 25
    Caption = #32487#32493#26356#25442#20070#30446
    TabOrder = 1
    OnClick = btgenhuanClick
  end
  object ds: TDataSource
    DataSet = query
    Left = 576
    Top = 56
  end
  object query: TADOQuery
    Parameters = <>
    Left = 600
    Top = 136
  end
end
