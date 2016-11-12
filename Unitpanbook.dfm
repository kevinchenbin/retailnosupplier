object frmpanbook: Tfrmpanbook
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #20070#30446#30424#28857
  ClientHeight = 324
  ClientWidth = 632
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
    Width = 632
    Height = 324
    Align = alClient
    Ctl3D = False
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnCellClick = DBGrid1CellClick
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
        FieldName = 'UserDefCode'
        Title.Alignment = taCenter
        Title.Caption = #33258#32534#30721
        Width = 60
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
        FieldName = 'PressCount'
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Width = 35
        Visible = True
      end>
  end
  object ds: TDataSource
    DataSet = query
    Left = 320
    Top = 104
  end
  object query: TADOQuery
    Parameters = <>
    Left = 224
    Top = 120
  end
end
