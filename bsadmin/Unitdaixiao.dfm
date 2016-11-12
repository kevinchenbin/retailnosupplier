object frmdaixiao: Tfrmdaixiao
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #30465#20195#37319#36141
  ClientHeight = 714
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
  object RzToolButton3: TRzToolButton
    Left = 226
    Top = -2
    Width = 60
    Height = 36
    Hint = 'View'
    DisabledIndex = 23
    GradientColorStyle = gcsSystem
    ImageIndex = 22
    UseToolbarButtonSize = False
    UseToolbarVisualStyle = False
    VisualStyle = vsGradient
    Caption = #21024#34892#13'[F4]'
  end
  object Label4: TLabel
    Left = 130
    Top = 681
    Width = 24
    Height = 17
    Caption = #21512#35745
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object lboperation: TLabel
    Left = 8
    Top = 681
    Width = 68
    Height = 17
    Caption = 'lboperation'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton2: TSpeedButton
    Left = 8
    Top = 210
    Width = 71
    Height = 22
    Caption = #23450#20301'(C)'
    Flat = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object Label12: TLabel
    Left = 192
    Top = 681
    Width = 48
    Height = 17
    Caption = #19978#26399#37319#36141
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object Label13: TLabel
    Left = 332
    Top = 681
    Width = 48
    Height = 17
    Caption = #26412#26399#25910#35746
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object Label14: TLabel
    Left = 467
    Top = 681
    Width = 48
    Height = 17
    Caption = #26412#26399#20195#38144
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object Label15: TLabel
    Left = 600
    Top = 681
    Width = 48
    Height = 17
    Caption = #26412#26399#37319#36141
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
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
    ButtonWidth = 60
    ShowButtonCaptions = True
    ShowDivider = False
    TextOptions = ttoSelectiveTextOnRight
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
    TabOrder = 1
    VisualStyle = vsClassic
    ToolbarControls = (
      tlbtn8
      BtnNew
      tlbtn1
      RzToolButton1
      RzToolButton4
      BtnView
      RzToolButton5
      RzToolButton2
      RzToolButton6
      BtnPrint
      BtnAlignBottom
      tlbtn7
      toolshowmainmenu)
    object tlbtn8: TRzToolButton
      Tag = 1
      Left = 1
      Top = -2
      Width = 55
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#21333#13'[F1]'
      OnClick = tlbtn8Click
    end
    object tlbtn1: TRzToolButton
      Tag = 3
      Left = 111
      Top = -2
      Width = 55
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20445#23384#13'[F3]'
      OnClick = tlbtn1Click
    end
    object tlbtn7: TRzToolButton
      Left = 636
      Top = -2
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
      Top = -2
      Width = 55
      Height = 36
      Hint = 'New'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #22686#21333#13'[F2]'
      OnClick = BtnNewClick
    end
    object BtnView: TRzToolButton
      Left = 286
      Top = -2
      Width = 60
      Height = 36
      Hint = 'View'
      DisabledIndex = 23
      GradientColorStyle = gcsSystem
      ImageIndex = 22
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21024#34892#13'[F4]'
      OnClick = D1Click
    end
    object BtnAlignBottom: TRzToolButton
      Left = 576
      Top = -2
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
      Left = 521
      Top = -2
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
      OnClick = BtnPrintClick
    end
    object RzToolButton1: TRzToolButton
      Left = 166
      Top = -2
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20462#25913#13'(&M)'
      Enabled = False
      OnClick = RzToolButton1Click
    end
    object RzToolButton2: TRzToolButton
      Left = 406
      Top = -2
      Width = 55
      Height = 36
      Hint = 'Print'
      DisabledIndex = 33
      GradientColorStyle = gcsSystem
      ImageIndex = 32
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#25171#21360#13'[F9]'
      OnClick = RzToolButton2Click
    end
    object RzToolButton4: TRzToolButton
      Left = 226
      Top = -2
      Width = 60
      Height = 36
      Hint = 'View'
      DisabledIndex = 23
      GradientColorStyle = gcsSystem
      ImageIndex = 22
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #32479#19968#13'[F5]'
      OnClick = RzToolButton4Click
    end
    object RzToolButton5: TRzToolButton
      Left = 346
      Top = -2
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#20070#13'(&F)'
      OnClick = RzToolButton5Click
    end
    object RzToolButton6: TRzToolButton
      Left = 461
      Top = -2
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'(&D)'
      Visible = False
      OnClick = RzToolButton6Click
    end
    object toolshowmainmenu: TRzToolButton
      Left = 696
      Top = -2
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
  object grpbxNtHeader: TGroupBox
    Left = 0
    Top = 121
    Width = 1012
    Height = 88
    Align = alTop
    Caption = #22270#20070#26816#32034
    Ctl3D = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 2
    object lblCatalog: TRzLabel
      Left = 26
      Top = 26
      Width = 24
      Height = 17
      Alignment = taRightJustify
      Caption = #20070#21495
      DragCursor = crHandPoint
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      OnMouseDown = lblCatalogMouseDown
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label1: TLabel
      Left = 257
      Top = 26
      Width = 24
      Height = 17
      Caption = #20070#21517
    end
    object Label6: TLabel
      Left = 572
      Top = 26
      Width = 24
      Height = 17
      Caption = #26399#21495
    end
    object Label7: TLabel
      Left = 417
      Top = 24
      Width = 24
      Height = 17
      Caption = #23450#20215
    end
    object Label8: TLabel
      Left = 413
      Top = 58
      Width = 36
      Height = 17
      Caption = #20986#29256#31038
    end
    object Label9: TLabel
      Left = 245
      Top = 58
      Width = 36
      Height = 17
      Caption = #33258#32534#30721
    end
    object Label11: TLabel
      Left = 756
      Top = 40
      Width = 24
      Height = 17
      Caption = #24448#26399
      Visible = False
    end
    object SpeedButton1: TSpeedButton
      Left = 602
      Top = 52
      Width = 111
      Height = 25
      Caption = #26597#30475#21382#21490#26126#32454
      OnClick = SpeedButton1Click
    end
    object spnewbook: TSpeedButton
      Left = 227
      Top = 22
      Width = 24
      Height = 23
      Caption = #26032
      Flat = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = spnewbookClick
    end
    object edname: TEdit
      Left = 287
      Top = 22
      Width = 114
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 0
    end
    object editselfcode: TEdit
      Left = 287
      Top = 54
      Width = 114
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 1
    end
    object editprice: TEdit
      Left = 455
      Top = 22
      Width = 111
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 2
    end
    object editpress: TEdit
      Left = 455
      Top = 54
      Width = 111
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 3
    end
    object edqihao: TEdit
      Left = 602
      Top = 22
      Width = 111
      Height = 23
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 4
    end
    object cbwangqi: TComboBoxEx
      Left = 746
      Top = 20
      Width = 111
      Height = 26
      ItemsEx = <>
      Ctl3D = False
      ItemHeight = 16
      ParentCtl3D = False
      TabOrder = 5
      Text = 'cbwangqi'
      Visible = False
    end
    object edtCatalog: TRzEdit
      Left = 56
      Top = 22
      Width = 170
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      MaxLength = 20
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 6
      OnKeyPress = edtCatalogKeyPress
    end
    object Richcopy: TRichEdit
      Left = 738
      Top = 28
      Width = 185
      Height = 40
      Font.Charset = GB2312_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Lines.Strings = (
        'Richcopy')
      ParentFont = False
      TabOrder = 7
      Visible = False
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 36
    Width = 1012
    Height = 85
    Align = alTop
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    object RzLabel2: TRzLabel
      Left = 360
      Top = 22
      Width = 24
      Height = 17
      Caption = #21333#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label3: TLabel
      Left = 524
      Top = 51
      Width = 24
      Height = 17
      Caption = #26085#26399
    end
    object lbl2: TRzLabel
      Left = 10
      Top = 22
      Width = 36
      Height = 17
      Caption = #20379#24212#21830
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel5: TRzLabel
      Left = 9
      Top = 53
      Width = 36
      Height = 17
      Caption = #37319#36141#21592
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl7: TRzLabel
      Left = 183
      Top = 51
      Width = 36
      Height = 17
      Caption = #38468#21152#36153
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label10: TLabel
      Left = 669
      Top = 17
      Width = 24
      Height = 17
      Caption = #22791#27880
    end
    object Label2: TLabel
      Left = 336
      Top = 51
      Width = 48
      Height = 17
      Caption = #37319#36141#25240#25187
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 507
      Top = 51
      Width = 11
      Height = 17
      Caption = '%'
    end
    object sbnewcustomer: TSpeedButton
      Left = 323
      Top = 17
      Width = 24
      Height = 23
      Caption = #26032
      Flat = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = sbnewcustomerClick
    end
    object dbedtRetailNtCode: TRzDBEdit
      Left = 390
      Top = 19
      Width = 110
      Height = 23
      DataSource = dsHeader
      DataField = 'Daixiaocode'
      ReadOnly = True
      AutoSize = False
      Ctl3D = False
      DisabledColor = clWindow
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 1
    end
    object DBNavigator1: TDBNavigator
      Left = 500
      Top = 19
      Width = 148
      Height = 23
      DataSource = dsHeader
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
      Flat = True
      TabOrder = 2
      OnClick = DBNavigator1Click
    end
    object cbcaigou: TComboBox
      Left = 51
      Top = 48
      Width = 103
      Height = 25
      BevelKind = bkFlat
      Ctl3D = False
      ItemHeight = 0
      ParentCtl3D = False
      TabOrder = 3
      OnKeyPress = cbcaigouKeyPress
    end
    object dbdate: TDateTimePicker
      Left = 554
      Top = 48
      Width = 95
      Height = 25
      BevelKind = bkFlat
      Date = 41243.672653530090000000
      Time = 41243.672653530090000000
      TabOrder = 4
    end
    object dm: TMemo
      Left = 699
      Top = 15
      Width = 294
      Height = 64
      Ctl3D = False
      HideSelection = False
      ParentCtl3D = False
      TabOrder = 5
    end
    object dbnbedtAddCosts: TRzNumericEdit
      Left = 225
      Top = 48
      Width = 100
      Height = 23
      TabOrder = 6
      OnKeyPress = dbnbedtAddCostsKeyPress
      DisplayFormat = #65509'###,##0.00;-'#65509'###,##0.00'
    end
    object cbclient: TComboBox
      Left = 99
      Top = 17
      Width = 226
      Height = 25
      BevelKind = bkFlat
      ItemHeight = 0
      TabOrder = 7
      OnKeyPress = cbclientKeyPress
    end
    object edtQryVendor: TEdit
      Left = 52
      Top = 17
      Width = 49
      Height = 25
      AutoSize = False
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 0
      OnKeyPress = edtQryVendorKeyPress
    end
    object editcaigoudiscount: TRzNumericEdit
      Left = 390
      Top = 48
      Width = 111
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 8
      OnClick = neorderClick
      OnKeyPress = editcaigoudiscountKeyPress
      IntegersOnly = False
      Value = 100.000000000000000000
      DisplayFormat = '##0.00'
    end
  end
  object dbgrid: TRzDBGrid
    Left = 1
    Top = 238
    Width = 1015
    Height = 435
    DataSource = dsnote
    DefaultDrawing = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = dbgridCellClick
    OnMouseUp = dbgridMouseUp
    OnTitleClick = dbgridTitleClick
    Columns = <
      item
        Expanded = False
        FieldName = 'xuhao'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #24207
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 45
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'clientname'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #23458#25143
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'shanqicaigou'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #19978#26399#37319#36141
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
        FieldName = 'benqiorder'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #26412#26399#25910#35746
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
        FieldName = 'benqidaixiao'
        Title.Alignment = taCenter
        Title.Caption = #26412#26399#20195#38144
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
        Title.Caption = #26412#26399#37319#36141
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
        FieldName = 'orderdiscount'
        Title.Alignment = taCenter
        Title.Caption = #25910#35746#25240#25187'%'
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
        FieldName = 'fahuofashi'
        PickList.Strings = (
          #31038#30452#21457
          #28100#36716#21457)
        Title.Alignment = taCenter
        Title.Caption = #21457#36135#26041#24335
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'remarks'
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 270
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ID'
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'clientid'
        Visible = False
      end>
  end
  object editcaigou: TEdit
    Left = 251
    Top = 680
    Width = 75
    Height = 25
    Alignment = taRightJustify
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    NumbersOnly = True
    ParentFont = False
    ReadOnly = True
    TabOrder = 4
  end
  object editorder: TEdit
    Left = 386
    Top = 680
    Width = 75
    Height = 25
    Alignment = taRightJustify
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    NumbersOnly = True
    ParentFont = False
    ReadOnly = True
    TabOrder = 5
  end
  object editdaixiao: TEdit
    Left = 521
    Top = 680
    Width = 75
    Height = 25
    Alignment = taRightJustify
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    NumbersOnly = True
    ParentFont = False
    ReadOnly = True
    TabOrder = 6
  end
  object editcaigoubeng: TEdit
    Left = 654
    Top = 680
    Width = 75
    Height = 25
    Alignment = taRightJustify
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    NumbersOnly = True
    ParentFont = False
    ReadOnly = True
    TabOrder = 7
  end
  object nedaixiao: TRzNumericEdit
    Left = 431
    Top = 213
    Width = 90
    Height = 19
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 8
    OnClick = nedaixiaoClick
    OnKeyPress = nedaixiaoKeyPress
    DisplayFormat = '0'
  end
  object necaigou: TRzNumericEdit
    Left = 523
    Top = 213
    Width = 90
    Height = 19
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 9
    OnClick = necaigouClick
    OnKeyPress = necaigouKeyPress
    DisplayFormat = '0'
  end
  object neorder: TRzNumericEdit
    Left = 614
    Top = 213
    Width = 90
    Height = 19
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 10
    OnClick = neorderClick
    OnKeyPress = neorderKeyPress
    IntegersOnly = False
    DisplayFormat = '##0.00'
  end
  object cbzhuanfa: TComboBox
    Left = 706
    Top = 213
    Width = 91
    Height = 25
    AutoComplete = False
    BevelKind = bkFlat
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ItemHeight = 17
    ItemIndex = 0
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 11
    Text = #31038#30452#21457
    OnKeyPress = cbzhuanfaKeyPress
    Items.Strings = (
      #31038#30452#21457
      #28100#36716#21457)
  end
  object editbk: TEdit
    Left = 800
    Top = 213
    Width = 193
    Height = 19
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 12
    OnKeyPress = editbkKeyPress
  end
  object GroupBox2: TGroupBox
    Left = -3
    Top = 231
    Width = 106
    Height = 138
    ParentBackground = False
    TabOrder = 13
    Visible = False
    object chfoceset: TCheckBox
      Left = 8
      Top = 14
      Width = 81
      Height = 17
      Caption = #26412#26399#20195#38144
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object chfsluru: TCheckBox
      Left = 8
      Top = 36
      Width = 81
      Height = 17
      Caption = #26412#26399#37319#36141
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object chfsamount: TCheckBox
      Left = 8
      Top = 60
      Width = 73
      Height = 17
      Caption = #25910#35746#25240#25187
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object chfsdiscount: TCheckBox
      Left = 8
      Top = 84
      Width = 81
      Height = 17
      Caption = #21457#36135#26041#24335
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object chjinjia: TCheckBox
      Left = 8
      Top = 107
      Width = 54
      Height = 17
      Caption = #22791#27880
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
  end
  object rb1: TRadioButton
    Left = 92
    Top = 215
    Width = 102
    Height = 17
    Caption = #35760#24405#25351#38024#21521#19979
    Checked = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    TabStop = True
  end
  object rb2: TRadioButton
    Left = 200
    Top = 215
    Width = 98
    Height = 17
    Caption = #35760#24405#25351#38024#21521#19978
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 15
  end
  object cbautochang: TCheckBox
    Left = 304
    Top = 215
    Width = 97
    Height = 17
    Caption = #22238#36710#33258#21160#25442#34892
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 16
  end
  object dsHeader: TDataSource
    DataSet = aqHeader
    Left = 600
    Top = 352
  end
  object aqHeader: TADOQuery
    Parameters = <>
    Left = 312
    Top = 360
  end
  object pm: TPopupMenu
    Left = 400
    Top = 384
    object N1: TMenuItem
      Caption = #20070'  '#21495
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #33258#32534#30721
      OnClick = N2Click
    end
    object N3: TMenuItem
      Caption = #20070'  '#21517
      OnClick = N3Click
    end
    object N4: TMenuItem
      Caption = #23450'  '#20215
      OnClick = N4Click
    end
    object N13: TMenuItem
      Caption = #20316'  '#32773
    end
  end
  object dsnote: TDataSource
    DataSet = aqnote
    OnDataChange = dsnoteDataChange
    Left = 352
    Top = 352
  end
  object aqnote: TADOQuery
    Parameters = <
      item
        Name = 'ID'
        DataType = ftInteger
        Value = Null
      end>
    SQL.Strings = (
      
        'select RANK() OVER(order by a.id desc) as xuhao,a.id,a.*,b.name ' +
        'as clientname from dbo.BS_DaixiaoNote a left join dbo.CUST_Custo' +
        'merInfo b'
      'on a.clientid = b.id'
      'where daixiaoheadid =:ID')
    Left = 237
    Top = 272
  end
  object dsetVendor: TADODataSet
    Parameters = <>
    Left = 120
    Top = 448
  end
  object dsrcVendor: TDataSource
    DataSet = dsetVendor
    Left = 293
    Top = 296
  end
  object PopupMenu1: TPopupMenu
    OnPopup = PopupMenu1Popup
    Left = 264
    Top = 376
    object D1: TMenuItem
      Caption = #21024#38500'(&D)'
      OnClick = D1Click
    end
    object N5: TMenuItem
      Caption = #20840#36873'(&C)'
      OnClick = N5Click
    end
    object N6: TMenuItem
      Caption = #24674#22797#19978#19968#27425#21024#38500
      OnClick = N6Click
    end
    object N8: TMenuItem
      Caption = '-'
    end
    object N7: TMenuItem
      Caption = #28155#21152#23458#25143'(&Z)'
      OnClick = N7Click
    end
    object N9: TMenuItem
      Caption = '-'
    end
    object F1: TMenuItem
      Caption = #22797#21046'(&F)'
      OnClick = F1Click
    end
    object N10: TMenuItem
      Caption = #31896#36148'(&N)'
      OnClick = N10Click
    end
  end
  object frxCrossObject1: TfrxCrossObject
    Left = 552
    Top = 448
  end
  object frxdbcaigoushengdai: TfrxDBDataset
    UserName = 'frxdbcaigoushengdai'
    CloseDataSource = False
    DataSet = adoreport
    Left = 176
    Top = 328
  end
  object adoreport: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'id'
        Size = -1
        Value = Null
      end>
    SQL.Strings = (
      
        'select  RANK() OVER(order by fahuofashi,a.id desc) as '#39#24207#21495#39',c.dao' +
        'zhan as '#39#21040#31449#39',c.name as '#39#23458#25143#21517#31216#39',a.benqicaigou as '#39#37319#36141#25968#39
      
        ',c.contact as '#39#32852#31995#20154#39',c.telephone as '#39#30005#35805#39',c.address as '#39#22320#22336#39',a.fahu' +
        'ofashi as '#39#21457#36135#26041#24335#39',a.remarks as '#39#22791#27880#39' from dbo.BS_DaixiaoNote a lef' +
        't join '
      'dbo.CUST_CustomerInfo c on a.clientid = c.id '
      'where daixiaoheadid=:id'
      'order by fahuofashi'
      '')
    Left = 104
    Top = 376
  end
  object aqtotalhuizhong: TADOQuery
    Parameters = <
      item
        Name = 'id'
        DataType = ftInteger
        Value = Null
      end>
    SQL.Strings = (
      ''
      'select sum(shanqicaigou) as shanqi,sum(benqiorder) as benqi,'
      
        'sum(benqidaixiao) as daixao,sum(benqicaigou)as benqicaigou from ' +
        'dbo.BS_DaixiaoNote where daixiaoheadid=:id')
    Left = 288
    Top = 464
  end
  object frxCrossObject2: TfrxCrossObject
    Left = 376
    Top = 448
  end
end
