object frmclientadddot: Tfrmclientadddot
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #23458#25143#25240#25187#21152#28857#35774#32622
  ClientHeight = 516
  ClientWidth = 773
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 17
  object Label2: TLabel
    Left = 349
    Top = 61
    Width = 48
    Height = 17
    Caption = #25240#25187#21152#28857
  end
  object Label3: TLabel
    Left = 468
    Top = 61
    Width = 11
    Height = 17
    Caption = '%'
  end
  object DBGrid2: TDBGrid
    Left = 323
    Top = 95
    Width = 446
    Height = 413
    Hint = #21491#38190#21487#20840#36873#25110#21024#38500
    Ctl3D = False
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentCtl3D = False
    ParentFont = False
    ParentShowHint = False
    PopupMenu = PopupMenu1
    ShowHint = True
    TabOrder = 6
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnCellClick = DBGrid2CellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'xuhao'
        Title.Alignment = taCenter
        Title.Caption = #24207#21495
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'clientname'
        Title.Alignment = taCenter
        Title.Caption = #23458#25143#21517#31216
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'typename'
        Title.Alignment = taCenter
        Title.Caption = #31867#21035
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'adddot'
        Title.Alignment = taCenter
        Title.Caption = #25240#25187#21152#28857'(%)'
        Width = 80
        Visible = True
      end>
  end
  object DBGrid1: TDBGrid
    Left = 4
    Top = 47
    Width = 285
    Height = 461
    Hint = #21491#38190#20840#36873
    Ctl3D = False
    DataSource = ds1
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentCtl3D = False
    ParentFont = False
    ParentShowHint = False
    PopupMenu = PopupMenu2
    ShowHint = True
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'clientname'
        Title.Alignment = taCenter
        Title.Caption = #23458#25143#21517#31216
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'typename'
        Title.Alignment = taCenter
        Title.Caption = #31867#21035
        Width = 60
        Visible = True
      end>
  end
  object edname: TEdit
    Left = 275
    Top = 8
    Width = 120
    Height = 25
    AutoSize = False
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 1
    OnChange = ednameChange
  end
  object eddot: TEdit
    Left = 400
    Top = 59
    Width = 64
    Height = 25
    AutoSize = False
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 2
  end
  object Button1: TButton
    Left = 502
    Top = 58
    Width = 75
    Height = 25
    Caption = #35774#32622
    TabOrder = 3
    OnClick = Button1Click
  end
  object cmtype: TComboBox
    Left = 74
    Top = 8
    Width = 120
    Height = 25
    BevelKind = bkFlat
    Ctl3D = False
    ItemHeight = 17
    ParentCtl3D = False
    TabOrder = 4
    OnChange = cmtypeChange
  end
  object Button2: TButton
    Left = 425
    Top = 8
    Width = 75
    Height = 25
    Caption = #26597#35810#23458#25143
    TabOrder = 5
    OnClick = Button2Click
  end
  object chname: TCheckBox
    Left = 229
    Top = 11
    Width = 44
    Height = 17
    Caption = #21517#31216
    TabOrder = 7
  end
  object chtype: TCheckBox
    Left = 5
    Top = 11
    Width = 68
    Height = 17
    Caption = #23458#25143#31867#22411
    TabOrder = 8
  end
  object fcon: TADOConnection
    Left = 616
    Top = 65528
  end
  object ds: TDataSource
    DataSet = query
    Left = 584
    Top = 32
  end
  object query: TADOQuery
    Parameters = <>
    Left = 664
    Top = 8
  end
  object PopupMenu1: TPopupMenu
    Left = 712
    Top = 112
    object N2: TMenuItem
      Caption = #20840#36873
      OnClick = N2Click
    end
    object N1: TMenuItem
      Caption = #21024#38500
      OnClick = N1Click
    end
  end
  object ds1: TDataSource
    DataSet = aq1
    Left = 200
    Top = 136
  end
  object aq1: TADOQuery
    Parameters = <>
    Left = 96
    Top = 208
  end
  object PopupMenu2: TPopupMenu
    Left = 240
    Top = 80
    object MenuItem1: TMenuItem
      Caption = #20840#36873
      OnClick = MenuItem1Click
    end
  end
end
