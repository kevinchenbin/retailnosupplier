object frmshengdaifahuo: Tfrmshengdaifahuo
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #30465#20195#21457#36135
  ClientHeight = 712
  ClientWidth = 1012
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 15
    Top = 161
    Width = 51
    Height = 17
    Caption = #21457#36135#25968#37327':'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 36
    Width = 996
    Height = 116
    Caption = #30465#20195#37319#36141#26816#32034
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label2: TLabel
      Left = 690
      Top = 25
      Width = 12
      Height = 17
      Caption = #21040
    end
    object sbsearch: TSpeedButton
      Left = 864
      Top = 20
      Width = 89
      Height = 37
      Caption = #26597#35810'(&S)'
      OnClick = sbsearchClick
    end
    object SpeedButton1: TSpeedButton
      Left = 864
      Top = 63
      Width = 89
      Height = 33
      Caption = #29983#25104#21457#36135#21333
      OnClick = SpeedButton1Click
    end
    object Label3: TLabel
      Left = 690
      Top = 55
      Width = 12
      Height = 17
      Caption = #21040
    end
    object edname: TEdit
      Left = 95
      Top = 50
      Width = 122
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 1
      OnChange = ednameChange
    end
    object cbruku: TCheckBox
      Left = 482
      Top = 25
      Width = 73
      Height = 17
      Caption = #37319#36141#26085#26399
      TabOrder = 2
    end
    object eduserdef: TEdit
      Left = 96
      Top = 21
      Width = 121
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 0
      OnChange = eduserdefChange
    end
    object edauthor: TEdit
      Left = 323
      Top = 22
      Width = 121
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 3
      OnChange = edauthorChange
    end
    object chauthor: TCheckBox
      Left = 257
      Top = 25
      Width = 57
      Height = 17
      Caption = #20316#32773
      TabOrder = 4
    end
    object chuserdef: TCheckBox
      Left = 16
      Top = 25
      Width = 61
      Height = 17
      Caption = #33258#32534#30721
      TabOrder = 5
    end
    object chname: TCheckBox
      Left = 16
      Top = 54
      Width = 49
      Height = 17
      Caption = #20070#21517
      TabOrder = 6
    end
    object edisbn: TEdit
      Left = 323
      Top = 51
      Width = 122
      Height = 23
      Ctl3D = False
      MaxLength = 13
      ParentCtl3D = False
      TabOrder = 7
      OnChange = edisbnChange
    end
    object chisbn: TCheckBox
      Left = 257
      Top = 54
      Width = 49
      Height = 17
      Caption = #20070#21495
      TabOrder = 8
    end
    object cbfahuofanshi: TCheckBox
      Left = 16
      Top = 83
      Width = 72
      Height = 17
      Caption = #21457#36135#26041#24335
      TabOrder = 9
    end
    object cbfahuo: TComboBox
      Left = 94
      Top = 79
      Width = 123
      Height = 25
      Style = csDropDownList
      ItemHeight = 17
      ItemIndex = 0
      TabOrder = 10
      Text = #31038#30452#21457
      OnChange = cbfahuoChange
      Items.Strings = (
        #31038#30452#21457
        #28100#36716#21457)
    end
    object cbrukuselect: TCheckBox
      Left = 482
      Top = 54
      Width = 73
      Height = 17
      Caption = #20837#24211#26085#26399
      TabOrder = 11
    end
    object dtpend: TDateTimePicker
      Left = 707
      Top = 21
      Width = 121
      Height = 25
      Date = 40909.661257361110000000
      Time = 40909.661257361110000000
      Checked = False
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MinDate = 40909.000000000000000000
      ParentFont = False
      TabOrder = 12
    end
    object dtpstart: TDateTimePicker
      Left = 561
      Top = 21
      Width = 123
      Height = 25
      Date = 40909.661257361110000000
      Time = 40909.661257361110000000
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MinDate = 40909.000000000000000000
      ParentFont = False
      TabOrder = 13
    end
    object dtrukubegin: TDateTimePicker
      Left = 561
      Top = 52
      Width = 123
      Height = 25
      Date = 40909.661257361110000000
      Time = 40909.661257361110000000
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MinDate = 40909.000000000000000000
      ParentFont = False
      TabOrder = 14
    end
    object rukudateend: TDateTimePicker
      Left = 708
      Top = 52
      Width = 120
      Height = 25
      Date = 40909.661257361110000000
      Time = 40909.661257361110000000
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MinDate = 40909.000000000000000000
      ParentFont = False
      TabOrder = 15
    end
  end
  object RzDBGrid1: TRzDBGrid
    Left = 0
    Top = 184
    Width = 996
    Height = 520
    DataSource = ds
    DefaultDrawing = True
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    PopupMenu = PopupMenu1
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = RzDBGrid1CellClick
    Columns = <
      item
        Expanded = False
        FieldName = 'xuhao'
        Title.Alignment = taCenter
        Title.Caption = #24207#21495
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'UserDefCode'
        Title.Alignment = taCenter
        Title.Caption = #33258#32534#30721
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'bookname'
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'price'
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Author'
        Title.Alignment = taCenter
        Title.Caption = #20316#32773
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'fahuofashi'
        Title.Alignment = taCenter
        Title.Caption = #21457#36135#26041#24335
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'clientname'
        Title.Alignment = taCenter
        Title.Caption = #23458#25143#21517#31216
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Daixiaocode'
        Title.Alignment = taCenter
        Title.Caption = #21333#21495
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'benqicaigou'
        Title.Alignment = taCenter
        Title.Caption = #37319#36141#25968#37327
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'orderdiscount'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #25240#25187'%'
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'discountprice'
        Title.Alignment = taCenter
        Title.Caption = #23454#27915
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'fixprice'
        Title.Alignment = taCenter
        Title.Caption = #30721#27915
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'bkcatalogid'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'clientid'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'diaxiaonoteid'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'fahuoamount'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #21457#36135#25968#37327
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Visible = True
      end>
  end
  object rztlbr1: TRzToolbar
    Left = 0
    Top = 0
    Width = 1012
    Height = 36
    AutoResize = False
    AutoStyle = False
    Margin = 1
    TopMargin = 4
    RowHeight = 29
    ButtonWidth = 60
    ShowButtonCaptions = True
    ShowDivider = False
    TextOptions = ttoCustom
    WrapControls = False
    BorderInner = fsFlatRounded
    BorderOuter = fsNone
    BorderSides = [sdTop, sdBottom]
    BorderWidth = 0
    Caption = #21024#38500
    Color = 16113353
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    GradientColorStyle = gcsMSOffice
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 2
    VisualStyle = vsClassic
    ToolbarControls = (
      tlbtn8
      BtnNew
      tlbtn1
      BtnPrint
      BtnView
      BtnAlignBottom
      tlbtn7
      toolshowmainmenu)
    object tlbtn8: TRzToolButton
      Tag = 1
      Left = 1
      Top = 0
      Width = 55
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#35810#13'[F1]'
      OnClick = tlbtn8Click
    end
    object tlbtn1: TRzToolButton
      Tag = 3
      Left = 111
      Top = 0
      Width = 55
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20445#23384#13'[F3]'
      Visible = False
    end
    object tlbtn7: TRzToolButton
      Left = 341
      Top = 0
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = tlbtn7Click
    end
    object BtnNew: TRzToolButton
      Tag = 2
      Left = 56
      Top = 0
      Width = 55
      Height = 36
      Hint = 'New'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21457#36135#13'[F2]'
      OnClick = SpeedButton1Click
    end
    object BtnView: TRzToolButton
      Left = 221
      Top = 0
      Width = 60
      Height = 36
      Hint = 'View'
      DisabledIndex = 23
      GradientColorStyle = gcsSystem
      ImageIndex = 22
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#20070#13'(F)'
      Visible = False
      OnClick = BtnViewClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 281
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 27
      GradientColorStyle = gcsSystem
      ImageIndex = 26
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26368#23567#21270#13'(N)'
      OnClick = BtnAlignBottomClick
    end
    object BtnPrint: TRzToolButton
      Left = 166
      Top = 0
      Width = 55
      Height = 36
      Hint = 'Print'
      DisabledIndex = 33
      GradientColorStyle = gcsSystem
      ImageIndex = 32
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25171#21360#13'[F10]'
      Visible = False
    end
    object toolshowmainmenu: TRzToolButton
      Left = 401
      Top = 0
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26174#31034#13#20027#33756#21333
      OnClick = toolshowmainmenuClick
    end
  end
  object editfahuo: TEdit
    Left = 73
    Top = 158
    Width = 93
    Height = 21
    NumbersOnly = True
    TabOrder = 3
    OnKeyPress = editfahuoKeyPress
  end
  object editcaigoutotal: TEdit
    Left = 660
    Top = 153
    Width = 82
    Height = 19
    Alignment = taRightJustify
    Ctl3D = False
    ParentCtl3D = False
    ReadOnly = True
    TabOrder = 4
  end
  object editfahuototal: TEdit
    Left = 791
    Top = 153
    Width = 82
    Height = 19
    Alignment = taRightJustify
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 5
  end
  object ds: TDataSource
    DataSet = aqnote
    Left = 408
    Top = 304
  end
  object aqnote: TADOQuery
    Parameters = <>
    Left = 376
    Top = 368
  end
  object ado: TADOConnection
    ConnectionTimeout = 600
    Left = 488
    Top = 248
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 504
    Top = 352
  end
  object adoexec: TADOQuery
    CommandTimeout = 600000
    Parameters = <>
    Left = 336
    Top = 280
  end
  object PopupMenu1: TPopupMenu
    Left = 264
    Top = 336
    object N1: TMenuItem
      Caption = #20840#36873
      OnClick = N1Click
    end
  end
end
