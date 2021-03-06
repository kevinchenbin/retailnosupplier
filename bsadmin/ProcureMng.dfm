inherited frmProcureMng: TfrmProcureMng
  BorderStyle = bsSingle
  Caption = #37319#36141#22788#29702
  ClientHeight = 712
  ClientWidth = 1012
  DoubleBuffered = True
  Position = poDefault
  PrintScale = poNone
  WindowState = wsMaximized
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  ExplicitWidth = 1018
  ExplicitHeight = 740
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel [0]
    Left = 526
    Top = 46
    Width = 106
    Height = 19
    Caption = '--'#37319#36141#22788#29702
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = #26999#20307
    Font.Style = [fsBold]
    ParentFont = False
  end
  object labtitle: TLabel [1]
    Left = 268
    Top = 46
    Width = 252
    Height = 19
    Alignment = taRightJustify
    Caption = #25104#37117#22521#24503#31185#25216#21457#23637#26377#38480#20844#21496
    Color = clBtnFace
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = #26999#20307
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    Transparent = True
  end
  object dbgrdNote: TRzDBGrid [2]
    Left = 1
    Top = 224
    Width = 1012
    Height = 460
    Hint = #21452#20987#21487#20462#25913#20070#30446#36164#26009
    DataSource = dsrcNote
    DefaultDrawing = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentFont = False
    ParentShowHint = False
    PopupMenu = selectmenu
    ReadOnly = True
    ShowHint = True
    TabOrder = 7
    TitleFont.Charset = GB2312_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnCellClick = dbgrdNoteCellClick
    OnDblClick = dbgrdNoteDblClick
    FixedLineColor = clDefault
    Columns = <
      item
        Expanded = False
        FieldName = 'xuhao'
        Title.Alignment = taCenter
        Title.Caption = #24207
        Width = 30
        Visible = True
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
        FieldName = 'CatalogName'
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
        Width = 75
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
        FieldName = 'Amount'
        Title.Alignment = taCenter
        Title.Caption = #25968#37327
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Discount'
        Title.Alignment = taCenter
        Title.Caption = #25240#25187'%'
        Width = 45
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'FixedPrice'
        Title.Alignment = taCenter
        Title.Caption = #30721#27915
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DiscountedPrice'
        Title.Alignment = taCenter
        Title.Caption = #23454#27915
        Width = 65
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
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PressCount'
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BkstackName'
        Title.Alignment = taCenter
        Title.Caption = #24211#20301
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'stkamount'
        Title.Alignment = taCenter
        Title.Caption = #24403#21069'/'#24635#24211#23384
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'detailbk'
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Width = 120
        Visible = True
      end>
  end
  object rztlbr1: TRzToolbar [3]
    Left = 0
    Top = 0
    Width = 1012
    Height = 37
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
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    GradientColorStyle = gcsCustom
    ParentFont = False
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      RzToolButton1
      mtbbtnAddNtHeader
      BtnSave
      BtnProperties
      tlbtn1
      tlbtn2
      tlbtn3
      RzToolButton2
      tlbtn4
      tlbtn5
      BtnClear
      BtnView
      BtnWeekView
      BtnFinish
      BtnAlignBottom
      tlbtn7
      toolshowmainmenu)
    object RzToolButton1: TRzToolButton
      Tag = 1
      Left = 1
      Top = 0
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#21333#13'[F1]'
      OnClick = tlbtn1Click
    end
    object tlbtn1: TRzToolButton
      Tag = 3
      Left = 231
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21024#21333#13'[F9]'
      Visible = False
      OnClick = tlbtn1Click
    end
    object tlbtn2: TRzToolButton
      Tag = 5
      Left = 281
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 24
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21024#34892#13'[F5]'
      OnClick = tlbtn1Click
    end
    object tlbtn3: TRzToolButton
      Tag = 6
      Left = 331
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #32479#19968#13'[F6]'
      OnClick = tlbtn1Click
    end
    object RzToolButton2: TRzToolButton
      Tag = 7
      Left = 381
      Top = 0
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 8
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #29616#22330#25910#13#27454'[F7]'
      Visible = False
      OnClick = tlbtn1Click
    end
    object tlbtn4: TRzToolButton
      Left = 441
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 10
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'[F8]'
      OnClick = tlbtn4Click
    end
    object tlbtn5: TRzToolButton
      Left = 491
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25171#21360'[F10]'
      OnClick = tlbtn5Click
    end
    object tlbtn7: TRzToolButton
      Left = 811
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = tlbtn7Click
    end
    object BtnClear: TRzToolButton
      Left = 541
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Clear'
      DisabledIndex = 21
      GradientColorStyle = gcsSystem
      ImageIndex = 26
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #39044#35272'[F11]'
      OnClick = BtnClearClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 751
      Top = 0
      Width = 60
      Height = 36
      DisabledIndex = 29
      GradientColorStyle = gcsSystem
      ImageIndex = 28
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26368#23567#21270#13'(N)'
      OnClick = BtnAlignBottomClick
    end
    object mtbbtnAddNtHeader: TRzToolButton
      Tag = 2
      Left = 61
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 30
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #22686#21333#13'[F2]'
      OnClick = tlbtn1Click
    end
    object BtnView: TRzToolButton
      Left = 591
      Top = 0
      Width = 50
      Height = 36
      Hint = 'View'
      DisabledIndex = 33
      GradientColorStyle = gcsSystem
      ImageIndex = 32
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#20070#13'(F)'
      OnClick = BtnViewClick
    end
    object BtnSave: TRzToolButton
      Left = 111
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Save'
      DisabledIndex = 35
      GradientColorStyle = gcsSystem
      ImageIndex = 1
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20445#23384#13'[F3]'
      OnClick = BtnSaveClick
    end
    object BtnProperties: TRzToolButton
      Left = 171
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Properties'
      DisabledIndex = 37
      GradientColorStyle = gcsSystem
      ImageIndex = 36
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20462#25913#21333#22836'[F4]'
      OnClick = BtnPropertiesClick
    end
    object BtnWeekView: TRzToolButton
      Left = 641
      Top = 0
      Width = 60
      Height = 36
      DisabledIndex = 39
      GradientColorStyle = gcsSystem
      ImageIndex = 38
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #35746#21333#13#31579#36873
      OnClick = BtnWeekViewClick
    end
    object BtnFinish: TRzToolButton
      Left = 701
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Finish'
      DisabledIndex = 41
      GradientColorStyle = gcsSystem
      ImageIndex = 40
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #34917#20070#19978#26550
      OnClick = BtnFinishClick
    end
    object toolshowmainmenu: TRzToolButton
      Left = 861
      Top = 0
      Width = 50
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26174#31034#13#20027#33756#21333
      OnClick = toolshowmainmenuClick
    end
  end
  object RzStatusBar1: TRzStatusBar [4]
    Left = 0
    Top = 684
    Width = 1012
    Height = 28
    AutoStyle = False
    BorderInner = fsBump
    BorderOuter = fsNone
    BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
    BorderWidth = 0
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object lbl11: TRzLabel
      Left = 7
      Top = 4
      Width = 36
      Height = 17
      Caption = #25805#20316#21592
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl12: TRzLabel
      Left = 434
      Top = 4
      Width = 36
      Height = 17
      Caption = #24635#25968#37327
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkColor = clBtnFace
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl13: TRzLabel
      Left = 550
      Top = 4
      Width = 36
      Height = 17
      Caption = #24635#30721#27915
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl14: TRzLabel
      Left = 669
      Top = 4
      Width = 36
      Height = 17
      Caption = #24635#23454#27915
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lblOpName: TRzLabel
      Left = 52
      Top = 4
      Width = 4
      Height = 17
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel1: TRzLabel
      Left = 865
      Top = 4
      Width = 48
      Height = 17
      Caption = #25171#21360#27425#25968
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkColor = clBtnFace
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object dbnbedt2: TRzDBNumericEdit
      Left = 479
      Top = 2
      Width = 65
      Height = 23
      DataSource = dsrcNtHeader
      DataField = 'TotalAmount'
      ReadOnly = True
      Alignment = taLeftJustify
      Color = clInfoBk
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      DisplayFormat = '###,##0;-###,##0'
    end
    object dbnbedt3: TRzDBNumericEdit
      Left = 595
      Top = 2
      Width = 65
      Height = 23
      DataSource = dsrcNtHeader
      DataField = 'FixedPrice'
      ReadOnly = True
      Alignment = taLeftJustify
      Color = clInfoBk
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      DisplayFormat = '###,##0.00;-###,##0.00'
    end
    object dbnbedt4: TRzDBNumericEdit
      Left = 711
      Top = 2
      Width = 65
      Height = 23
      DataSource = dsrcNtHeader
      DataField = 'DiscountedPrice'
      ReadOnly = True
      Alignment = taLeftJustify
      Color = clInfoBk
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
      DisplayFormat = '###,##0.00;-###,##0.00'
    end
    object RzDBNumericEdit1: TRzDBNumericEdit
      Left = 924
      Top = 2
      Width = 65
      Height = 23
      DataSource = dsrcNtHeader
      DataField = 'printcount'
      ReadOnly = True
      Alignment = taLeftJustify
      Color = clInfoBk
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 3
      DisplayFormat = '###,##0'
    end
  end
  object GroupBox1: TGroupBox [5]
    Left = 0
    Top = 68
    Width = 1012
    Height = 77
    Ctl3D = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 3
    object lbl2: TRzLabel
      Left = 4
      Top = 15
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
    object lbl3: TRzLabel
      Left = 369
      Top = 46
      Width = 48
      Height = 17
      Caption = #37319#36141#26085#26399
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl4: TRzLabel
      Left = 393
      Top = 15
      Width = 24
      Height = 17
      Caption = #21333#21495
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl7: TRzLabel
      Left = 177
      Top = 46
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
    object lbl1: TRzLabel
      Left = 747
      Top = 15
      Width = 24
      Height = 17
      Caption = #22791#27880
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzButton1: TSpeedButton
      Left = 320
      Top = 12
      Width = 25
      Height = 23
      Caption = #26032
      Flat = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = RzButton1Click
    end
    object RzLabel2: TRzLabel
      Left = 573
      Top = 46
      Width = 48
      Height = 17
      Caption = #39044#21040#26085#26399
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel5: TRzLabel
      Left = 3
      Top = 46
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
    object edtQryVendor: TRzEdit
      Left = 42
      Top = 12
      Width = 43
      Height = 23
      Ctl3D = False
      DisabledColor = clWindow
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      OnKeyPress = edtQryVendorKeyPress
    end
    object dbnbedtAddCosts: TRzDBNumericEdit
      Left = 219
      Top = 44
      Width = 100
      Height = 23
      DataSource = dsrcNtHeader
      DataField = 'AddCosts'
      Alignment = taLeftJustify
      Color = clWhite
      Ctl3D = False
      DisabledColor = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      OnKeyPress = dblkpcbbVendorIDKeyPress
      IntegersOnly = False
      DisplayFormat = '###,##0.00;-###,##0.00'
    end
    object dbedtWsaleNtCode: TRzDBEdit
      Left = 423
      Top = 12
      Width = 183
      Height = 23
      DataSource = dsrcNtHeader
      DataField = 'Procurestr'
      ReadOnly = True
      Ctl3D = False
      DisabledColor = clWindow
      Enabled = False
      FocusColor = cl3DLight
      ParentCtl3D = False
      TabOrder = 2
    end
    object dblkpcbbVendorID: TRzDBLookupComboBox
      Left = 84
      Top = 12
      Width = 235
      Height = 23
      Ctl3D = False
      DataField = 'VendorID'
      DataSource = dsrcNtHeader
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ImeMode = imChinese
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcVendor
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 3
      OnKeyPress = dblkpcbbVendorIDKeyPress
      DisabledColor = clWindow
      SelectOnTab = True
    end
    object dblkpcbbStaffID: TRzDBLookupComboBox
      Left = 42
      Top = 44
      Width = 100
      Height = 23
      Ctl3D = False
      DataField = 'StaffID'
      DataSource = dsrcNtHeader
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcStaff
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
      DisabledColor = clWhite
    end
    object membk: TMemo
      Left = 777
      Top = 12
      Width = 230
      Height = 55
      Hint = #24405#20837#22791#27880#21518#22238#36710#20445#23384
      Ctl3D = False
      HideSelection = False
      Lines.Strings = (
        '')
      ParentCtl3D = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnExit = membkExit
      OnKeyPress = membkKeyPress
    end
    object dbdtedtHdTime: TDateTimePicker
      Left = 423
      Top = 41
      Width = 98
      Height = 25
      Date = 40920.744780439820000000
      Time = 40920.744780439820000000
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 6
    end
    object dbdtedtHdyujiTime: TDateTimePicker
      Left = 625
      Top = 42
      Width = 98
      Height = 25
      Date = 40920.744780439820000000
      Time = 40920.744780439820000000
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 7
    end
  end
  object dgdetail: TRzDBGrid [6]
    Left = 712
    Top = 224
    Width = 300
    Height = 460
    Anchors = [akLeft, akTop, akBottom]
    DataSource = ds2
    DefaultDrawing = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    TabOrder = 6
    TitleFont.Charset = GB2312_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Visible = False
    FixedLineColor = clDefault
    AltRowShading = True
    AltRowShadingColor = clBtnFace
    Columns = <
      item
        Expanded = False
        FieldName = 'ProcureNtCode'
        Title.Alignment = taCenter
        Title.Caption = #37319#36141#21333#21495
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Amount'
        Title.Alignment = taCenter
        Title.Caption = #25968#37327
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'RecAmount'
        Title.Caption = #24050#21040#25968#37327
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Discount'
        Title.Alignment = taCenter
        Title.Caption = #25240#25187
        Width = 45
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name'
        Title.Alignment = taCenter
        Title.Caption = #20379#36135#21830
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'HdTime'
        Title.Alignment = taCenter
        Title.Caption = #26085#26399
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Price'
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Visible = False
      end>
  end
  object DBNavigator1: TDBNavigator [7]
    Left = 607
    Top = 80
    Width = 116
    Height = 23
    DataSource = dsheader
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
    Flat = True
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 2
    OnClick = DBNavigator1Click
  end
  object GroupBox2: TGroupBox [8]
    Left = 0
    Top = 147
    Width = 1012
    Height = 75
    ParentBackground = False
    TabOrder = 5
    object lblCatalog: TRzLabel
      Left = 16
      Top = 14
      Width = 24
      Height = 17
      Alignment = taRightJustify
      Caption = #20070#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
      PopupMenu = pm
      OnMouseDown = lblCatalogMouseDown
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl8: TRzLabel
      Left = 16
      Top = 45
      Width = 24
      Height = 17
      Caption = #25968#37327
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl9: TRzLabel
      Left = 189
      Top = 45
      Width = 24
      Height = 17
      Caption = #25240#25187
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label1: TLabel
      Left = 325
      Top = 45
      Width = 11
      Height = 17
      Caption = '%'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object spnewbook: TSpeedButton
      Left = 320
      Top = 11
      Width = 25
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
    object SpeedButton1: TSpeedButton
      Left = 924
      Top = 11
      Width = 72
      Height = 22
      Caption = #23450#20301'(C)'
      Flat = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = SpeedButton1Click
    end
    object RzLabel3: TRzLabel
      Left = 393
      Top = 45
      Width = 24
      Height = 17
      Caption = #22791#27880
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label8: TLabel
      Left = 393
      Top = 14
      Width = 24
      Height = 17
      Caption = #36827#20215
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object dbnbedtAmount: TRzDBNumericEdit
      Left = 42
      Top = 43
      Width = 100
      Height = 23
      TabStop = False
      DataSource = dsrcNote
      DataField = 'Amount'
      Alignment = taLeftJustify
      Ctl3D = False
      DisabledColor = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      OnExit = dbnbedtAmountExit
      OnKeyPress = dbnbedtAmountKeyPress
      Max = 20000.000000000000000000
      DisplayFormat = '###,##0;-###,##0'
    end
    object edtCatalog: TRzEdit
      Left = 42
      Top = 11
      Width = 277
      Height = 23
      AutoSelect = False
      AutoSize = False
      Ctl3D = False
      DisabledColor = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      OnKeyPress = edtCatalogKeyPress
    end
    object dbnbedtDiscount: TRzDBNumericEdit
      Left = 219
      Top = 43
      Width = 100
      Height = 23
      DataSource = dsrcNote
      DataField = 'Discount'
      Alignment = taLeftJustify
      Ctl3D = False
      DisabledColor = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
      OnExit = dbnbedtDiscountExit
      OnKeyPress = dbnbedtDiscountKeyPress
      BlankValue = 100.000000000000000000
      CheckRange = True
      IntegersOnly = False
      Max = 100.000000000000000000
      DisplayFormat = '##0.00'
    end
    object editdetailbk: TEdit
      Left = 423
      Top = 43
      Width = 584
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 3
      OnKeyPress = editdetailbkKeyPress
    end
    object editjingjia: TEdit
      Left = 423
      Top = 11
      Width = 97
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
      OnExit = editjingjiaExit
      OnKeyPress = editjingjiaKeyPress
    end
    object CheckBox1: TCheckBox
      Left = 789
      Top = 16
      Width = 97
      Height = 17
      Caption = #26174#31034#21382#21490#26126#32454
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = CheckBox1Click
    end
  end
  object GroupBox3: TGroupBox [9]
    Left = 892
    Top = 184
    Width = 104
    Height = 113
    ParentBackground = False
    TabOrder = 4
    Visible = False
    object chfoceset: TCheckBox
      Left = 15
      Top = 15
      Width = 75
      Height = 17
      Caption = #23450#20301
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object chfsluru: TCheckBox
      Left = 15
      Top = 38
      Width = 44
      Height = 17
      Caption = #24405#20837
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = chfsluruClick
    end
    object chfsamount: TCheckBox
      Left = 15
      Top = 61
      Width = 47
      Height = 17
      Caption = #25968#37327
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = chfsluruClick
    end
    object chfsdiscount: TCheckBox
      Left = 15
      Top = 84
      Width = 54
      Height = 17
      Caption = #25240#25187
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = chfsluruClick
    end
  end
  object pm1: TPopupMenu [10]
    Left = 16
    Top = 40
    object mniBsNote: TMenuItem
      Tag = 1
      AutoCheck = True
      Caption = #37319#36141#21333
      Checked = True
      GroupIndex = 1
      RadioItem = True
      OnClick = mniBsNoteSendbackClick
    end
    object mniBsNoteSendback: TMenuItem
      Tag = 2
      AutoCheck = True
      Caption = #37319#36141#25764#28040#21333
      GroupIndex = 1
      RadioItem = True
      OnClick = mniBsNoteSendbackClick
    end
  end
  object dsrcNtHeader: TDataSource [11]
    DataSet = dsetNtHeader
    Left = 296
    Top = 328
  end
  object dsetNtHeader: TADODataSet [12]
    CursorType = ctOpenForwardOnly
    Parameters = <>
    Left = 40
    Top = 344
  end
  object dsrcNote: TDataSource [13]
    DataSet = dsetNote
    Left = 288
    Top = 536
  end
  object dsetNote: TADODataSet [14]
    AfterScroll = dsetNoteAfterScroll
    Parameters = <>
    Left = 608
    Top = 440
  end
  object dsetVendor: TADODataSet [15]
    CommandText = 
      'select * from CUST_CustomerInfo where  Type=1 and customerstate=' +
      '1 order by name'
    Parameters = <>
    Left = 208
    Top = 272
  end
  object dsrcVendor: TDataSource [16]
    DataSet = dsetVendor
    Left = 160
    Top = 224
  end
  object dsrcStaff: TDataSource [17]
    DataSet = dsetStaff
    Left = 232
    Top = 312
  end
  object dsetStaff: TADODataSet [18]
    CommandText = 'select ID, Name from SYS_StaffInfo where Career=2'
    Parameters = <>
    Left = 480
    Top = 312
  end
  object dsetBkstack: TADODataSet [19]
    CursorType = ctStatic
    CommandText = 'select ID, Name from STK_BookstackInfo'
    Parameters = <>
    Left = 80
    Top = 392
  end
  object dsrcBkstack: TDataSource [20]
    DataSet = dsetBkstack
    Left = 288
    Top = 280
  end
  object dblkpdlgVendor: TRzDBLookupDialog [21]
    Dataset = dsetLkpVendor
    GridOptions = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    MoveSearchField = False
    SearchField = 'Name'
    ShowNavigator = False
    Caption = #36873#25321#20070#30446
    CaptionOK = #30830#35748
    CaptionCancel = #21462#28040
    CaptionHelp = '&Help'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Left = 56
    Top = 424
  end
  object dsetLkpVendor: TADODataSet [22]
    CursorType = ctStatic
    CommandText = 'select * from CUST_CustomerInfo where ID=0 or (ID>0 and Type=2)'
    Parameters = <>
    Left = 80
    Top = 272
  end
  object cmdUpdateNtHeader: TADOCommand [23]
    CommandText = 'USP_BS_Update_NtHeader;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@HdTime'
        Attributes = [paNullable]
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@StgID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@CustomerID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Remarks'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 500
        Value = Null
      end
      item
        Name = '@StaffID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@AddCosts'
        Attributes = [paNullable]
        DataType = ftFloat
        Precision = 15
        Value = Null
      end
      item
        Name = '@SupplySN'
        Attributes = [paNullable]
        DataType = ftString
        Size = 50
        Value = Null
      end
      item
        Name = '@CardMoney'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@Cash'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@State'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@yijidate'
        DataType = ftDateTime
        Value = Null
      end>
    Left = 384
    Top = 400
  end
  object spQryNtHeader: TADOStoredProc [24]
    ProcedureName = 'USP_BS_Qry_NtHeader;1'
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Prepared = True
    Left = 408
    Top = 328
  end
  object spQryNtHeader1: TADOStoredProc [25]
    ProcedureName = 'USP_BS_Qry_NtHeader1;1'
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@NtCode'
        Attributes = [paNullable]
        DataType = ftString
        Size = 15
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Prepared = True
    Left = 480
    Top = 432
  end
  object cmdDelNtHeader: TADOCommand [26]
    CommandText = 'USP_BS_Del_NtHeader;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 400
    Top = 456
  end
  object cmdAddNote: TADOCommand [27]
    CommandText = 'USP_BS_Add_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@NtHeaderID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@BkcatalogID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@STKinfoID'
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@SupplierID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@NoteMode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 424
    Top = 264
  end
  object cmdUpdateNote: TADOCommand [28]
    CommandText = 'USP_BS_Update_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Amount'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Discount'
        Attributes = [paNullable]
        DataType = ftFloat
        Precision = 15
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 128
    Top = 328
  end
  object cmdDelNote: TADOCommand [29]
    CommandText = 'USP_BS_Del_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 352
    Top = 264
  end
  object cmdBatchUpdateNote: TADOCommand [30]
    CommandText = 'USP_BS_BatchUpdate_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@IDS'
        Attributes = [paNullable]
        DataType = ftString
        Size = 2147483647
        Value = Null
      end
      item
        Name = '@Amount'
        Attributes = [paNullable]
        DataType = ftString
        Precision = 10
        Size = -1
        Value = Null
      end
      item
        Name = '@Discount'
        Attributes = [paNullable]
        DataType = ftString
        Precision = 15
        Size = -1
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 168
    Top = 408
  end
  object cmdBatchDelNote: TADOCommand [31]
    CommandText = 'USP_BS_BatchDel_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@IDS'
        Attributes = [paNullable]
        DataType = ftString
        Size = 2147483647
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 136
    Top = 448
  end
  object cmdAddNtHeader: TADOCommand [32]
    CommandText = 'USP_BS_Add_NtHeader;1'
    CommandType = cmdStoredProc
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@OperatorID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@StgID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@CustomerID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 344
    Top = 368
  end
  inherited qryUserAuthority: TADOQuery
    Left = 552
    Top = 456
  end
  inherited aquerybs: TADOQuery
    Left = 552
    Top = 280
  end
  object cmdResetNtHeader: TADOCommand
    CommandText = 'USP_BS_Reset_NtHeader;1'
    CommandType = cmdStoredProc
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 304
    Top = 432
  end
  object ImageList1: TImageList
    Left = 784
    Top = 40
    Bitmap = {
      494C01012A005000A00110001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      000000000000360000002800000040000000B0000000010020000000000000B0
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000080808000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008080800000000000000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008080800080808000808080008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000080808000FFFFFF0000000000000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000080808000FFFFFF0080808000808080008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000FFFFFF00FFFFFF0080808000FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000FFFFFF008080800080808000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000FFFFFF008080800080808000FFFFFF008080800080808000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000000000000000
      0000000000000000000000000000808080000000000000000000000000000000
      0000000000000000000000000000666699000000000080808000808080008080
      8000808080008080800080808000808080008080800080808000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00FFFFFF000000
      0000FFFFFF000000000000000000C0C0C0000000000000000000000000000000
      00000000000000000000666699003399CC0080808000FFFFFF00FFFFFF008080
      8000FFFFFF008080800080808000C0C0C0008080800080808000808080000000
      0000000000000000000099999900CCCCCC000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00000000000000
      0000FFFFFF0080808000C0C0C000FFFFFF008080800000000000FFFFFF008080
      800000000000666699003399CC0066CCFF0080808000FFFFFF00808080008080
      8000FFFFFF0080808000C0C0C000FFFFFF008080800080808000FFFFFF008080
      80000000000099999900CCCCCC00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800000000000000000000000
      0000808080000000000000000000FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00666699003399CC0066CCFF00000000008080800080808000808080008080
      8000808080008080800080808000FFFFFF0080808000FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000000000000000000000000000000000000000000000000000FFFFFF006666
      99003399CC0066CCFF0000000000000000000000000080808000808080008080
      8000808080008080800080808000808080008080800080808000FFFFFF009999
      9900CCCCCC00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C0000000000000000000FFFFFF00000000000000000000000000666699003399
      CC0066CCFF000000000000000000000000000000000080808000C0C0C000C0C0
      C0008080800080808000FFFFFF0080808000808080008080800099999900CCCC
      CC00FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000C0C0C000FFFF
      FF0000000000FFFFFF00FFFFFF00FFFFFF0000000000666699003399CC0066CC
      FF00000000000000000000000000000000000000000080808000C0C0C000FFFF
      FF0080808000FFFFFF00FFFFFF00FFFFFF008080800099999900CCCCCC00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      80000000000000000000FFFFFF00FFFFFF00666699003399CC0066CCFF000000
      0000000000000000000000000000000000000000000000000000808080008080
      80008080800080808000FFFFFF00FFFFFF0099999900CCCCCC00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000666699003399CC0066CCFF00000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      800080808000808080008080800099999900CCCCCC00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000666699003399CC0066CCFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000808080008080800099999900CCCCCC00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000666699003399CC0066CCFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC666600CC666600CC66
      6600CC666600CC666600CC666600CC666600CC666600CC666600CC666600CC66
      6600CC666600CC666600CC666600CC6666000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000000000000000000000999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000009900FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000009999990000000000999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF0099330000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFF
      FF00FFFFFF00993300009933000099330000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00999999009999990099999900CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000000000000000000000999999000000000000000000CC996600FFFF
      FF009933000099330000993300009933000099330000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC009999990099999900999999009999990099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000009900FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000009900FFFFFF00CC6666000000000099999900000000000000
      000000000000000000009999990000000000CCCCCC0000000000000000000000
      0000000000009999990000000000999999000000000000000000CC996600FFFF
      FF009933000099330000FFFFFF00993300009933000099330000FFFFFF00FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC009999990099999900CCCCCC00999999009999990099999900CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00CC6666000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFF
      FF0099330000FFFFFF00FFFFFF00FFFFFF00993300009933000099330000FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC0099999900CCCCCC00CCCCCC00CCCCCC00999999009999990099999900CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000000000000000000000999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009933000099330000FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999990099999900CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000000000000000000000999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0099330000FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000009900FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000009900FFFFFF00CC6666000000000099999900000000000000
      000000000000000000009999990000000000CCCCCC0000000000000000000000
      0000000000009999990000000000999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC9966000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC666600FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00CC6666000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC99
      6600CC996600CC9966000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999
      99009999990099999900000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000000000000000000000999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5
      E500CC996600000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCC
      CC009999990000000000000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000000000000000000000999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC99
      660000000000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999
      99000000000000000000000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC6666000000000099999900000000000000
      000000000000000000000000000000000000CCCCCC0000000000000000000000
      0000000000000000000000000000999999000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC9966000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999000000
      00000000000000000000000000000000000000000000CC666600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000009900FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000009900FFFFFF00CC6666000000000099999900000000000000
      000000000000000000009999990000000000CCCCCC0000000000000000000000
      0000000000009999990000000000999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC666600CC666600CC66
      6600CC666600CC666600CC666600CC666600CC666600CC666600CC666600CC66
      6600CC666600CC666600CC666600CC6666000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900999999009999990000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC0066999900666699009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC00B2B2B200999999009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000099330000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC00999999000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC009999990000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000099330000CC660000CC66
      0000CC660000993300009933000099330000993300009933000099330000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00999999009999990099999900999999009999990099999900CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E5000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC660000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B2000000000099330000CC660000CC66
      0000993300009933000099330000993300009933000099330000993300009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999009999990099999900999999009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC00999999000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC0099999900000000000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000099330000CC6600009933
      0000FFFFFF00993300009933000099330000993300009933000099330000FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00999999009999990099999900999999009999990099999900FFFF
      FF0099999900CCCCCC0099999900000000000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC0099999900000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B2000000000099330000E5E5E5009933
      0000FFFFFF00993300009933000099330000993300009933000099330000FFFF
      FF00993300009933000099330000000000000000000099999900E5E5E5009999
      9900FFFFFF00999999009999990099999900999999009999990099999900FFFF
      FF00999999009999990099999900000000000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E5000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC0099999900000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E500000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000099330000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00000000009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00000000009999990000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0000000000999999009999
      99009999990099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5
      E500CC9966000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC99
      6600000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000000000000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC9966000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC99990099330000CC9999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0099999900CCCCCC000000000000000000000000000000
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000000000000CCCCCC000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9999009933000099330000993300000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900CCCCCC0099999900999999009999990000000000000000003333CC000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF008080
      8000993300009933000099330000CC9999000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000999999009999990099999900CCCCCC0000000000000000003333CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      0000000000000000FF000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E5008080800080808000808080009933
      00009933000099330000CC99990000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC008080800080808000808080009999
      99009999990099999900CCCCCC00000000000000000000000000000000003333
      CC000066FF000000CC0000000000000000000000000000000000000000000000
      00000000FF000000000000000000000000000000000000000000000000009999
      9900E5E5E5009999990000000000000000000000000000000000000000000000
      0000CCCCCC0000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00E5E5E50099996600FFFFCC00FFFFCC00FFFFFF00CCCC
      990099330000CC99990000000000000000000000000099999900000000000000
      00000000000000000000CCCCCC0099999900E5E5E500E5E5E500FFFFFF00E5E5
      E50099999900CCCCCC0000000000000000000000000000000000000000000000
      00000000CC000000FF0000009900000000000000000000000000000000000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC009999990000000000000000000000000000000000CCCC
      CC009999990000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFCC00FFFFCC00FFFFCC00FFFF
      FF0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500E5E5E500E5E5E500E5E5E500FFFF
      FF00666666000000000000000000000000000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000FF000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000CCCCCC009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0099999900F2EABF00FFFFFF00F2EABF00FFFFCC00FFFF
      CC00666666000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900E5E5E500FFFFFF00E5E5E500E5E5E500E5E5
      E500666666000000000000000000000000000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000FF00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC0099999900CCCCCC00999999000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFFF00FFFFFF00F2EABF00FFFF
      CC0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500FFFFFF00FFFFFF00E5E5E500E5E5
      E500666666000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000CC000000FF0000009900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC0099999900000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0099999900F2EABF00F2EABF00F2EABF009999
      6600808080000000000000000000000000000000000099999900000000000000
      000000000000000000000000000099999900E5E5E500E5E5E500E5E5E5009999
      9900808080000000000000000000000000000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000CC00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC009999990099999900999999000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500999999009999990099999900E5E5
      E500CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999990099999900E5E5
      E500999999000000000000000000000000000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000CC000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000999999009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC9966000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000000000000000000000000000000000000000000000000
      CC000000FF000000FF0000009900000000000000000000000000000000000000
      CC00000099000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000009999
      99009999990000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC996600CC996600CC99
      6600CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC000000000099999900999999009999
      99009999990000000000000000000000000000000000000000000000CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      00000000CC00000099000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      00009999990099999900000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5E500CC99
      6600000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900E5E5E5009999
      9900000000000000000000000000000000000000000000000000666699000000
      CC00666699000000000000000000000000000000000000000000000000000000
      000000000000000000000000CC00000000000000000000000000CCCCCC009999
      9900CCCCCC000000000000000000000000000000000000000000000000000000
      00000000000000000000999999000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC9966000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600000000000000
      0000000000000000000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000000000FFFF
      FF00FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000000000FFFF
      FF00FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      000000000000000000000000000000000000CC666600CC666600CC666600CC66
      6600CC666600CC666600CC666600CC666600CC666600CC666600CC666600CC66
      6600CC666600CC666600CC666600CC6666009999990099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900999999009999990099999900FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008080800000009900000099000000990000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008080800066666600666666006666660000000000000000000000
      000000000000000000000000000000000000CC666600FFFFFF00FFFFFF00FFCC
      CC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC666600999999000000000000000000CCCC
      CC000000000000000000CCCCCC000000000000000000CCCCCC00000000000000
      0000CCCCCC00000000000000000099999900FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00808080000000CC0000009900000099000000990000009900000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00808080009999990066666600666666006666660066666600000000000000
      000000000000000000000000000000000000CC666600FFFFFF00FFFFFF00FFCC
      CC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC666600999999000000000000000000CCCC
      CC000000000000000000CCCCCC000000000000000000CCCCCC00000000000000
      0000CCCCCC00000000000000000099999900FFFFFF00FFFFFF00FFFFFF00FFFF
      FF000000CC000000CC000000CC00000099000000990000009900000099000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00999999009999990099999900666666006666660066666600666666000000
      000000000000000000000000000000000000CC666600FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00CC66660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900FFFFFF0000000000FFFFFF000000
      00000000FF000000CC000000CC000000CC000000990000009900000099000099
      990000000000000000000000000000000000FFFFFF0000000000FFFFFF000000
      0000CCCCCC009999990099999900999999006666660066666600666666006666
      660000000000000000000000000000000000CC666600FFFFFF00FFFFFF00FFCC
      CC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC666600999999000000000000000000CCCC
      CC000000000000000000CCCCCC000000000000000000CCCCCC00000000000000
      0000CCCCCC000000000000000000999999000000000000000000000000000000
      00000000FF000000FF000000CC000000CC000000CC00000099000099990000CC
      CC00009999000000000000000000000000000000000000000000000000000000
      0000CCCCCC00CCCCCC0099999900999999009999990066666600666666009999
      990066666600000000000000000000000000CC666600FFFFFF00FFFFFF00FFCC
      CC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC666600999999000000000000000000CCCC
      CC000000000000000000CCCCCC000000000000000000CCCCCC00000000000000
      0000CCCCCC000000000000000000999999000000000000000000000000000000
      0000000000000000FF000000FF000000CC000000CC000099990000CCCC0000CC
      CC0000CCCC000099990000000000000000000000000000000000000000000000
      000000000000CCCCCC00CCCCCC00999999009999990066666600999999009999
      990099999900666666000000000000000000CC666600FFCCCC00FFCCCC000000
      9900000099000000990000009900FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00CC66660099999900CCCCCC00CCCCCC009999
      9900999999009999990099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000000000000000FF000000800000CCCC0000FFFF0000FFFF0000CC
      CC0000CCCC0000CCCC0000999900000000000000000000000000000000000000
      00000000000000000000CCCCCC006666660099999900CCCCCC00CCCCCC009999
      990099999900999999006666660000000000CC666600FFFFFF00FFFFFF000000
      9900FFFFFF00FFFFFF0000009900FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC6666009999990000000000000000009999
      99000000000000000000999999000000000000000000CCCCCC00000000000000
      0000CCCCCC000000000000000000999999000000000000000000000000000000
      000000000000000000000000000000CCCC0000FFFF00FFFFFF00C0C0C00000FF
      FF0000CCCC0000CCCC0000CCCC00009999000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC00FFFFFF00C0C0C000CCCC
      CC0099999900999999009999990066666600CC666600FFFFFF00FFFFFF000000
      9900FFFFFF00FFFFFF0000009900FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC6666009999990000000000000000009999
      99000000000000000000999999000000000000000000CCCCCC00000000000000
      0000CCCCCC000000000000000000999999000000000000000000000000000000
      00000000000000000000000000000000000000CCCC0000FFFF00FFFFFF00C0C0
      C00000FFFF0000CCCC0000999900993300000000000000000000000000000000
      00000000000000000000000000000000000099999900CCCCCC00FFFFFF00C0C0
      C000CCCCCC00999999006666660066666600CC666600FFCCCC00FFCCCC000000
      9900000099000000990000009900FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00CC66660099999900CCCCCC00CCCCCC009999
      9900999999009999990099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000CCCC0000FFFF00FFFF
      FF0000FFFF0000999900CC660000993300000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00FFFF
      FF00CCCCCC00666666009999990066666600CC666600FFFFFF00FFFFFF00FFCC
      CC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC666600999999000000000000000000CCCC
      CC000000000000000000CCCCCC000000000000000000CCCCCC00000000000000
      0000CCCCCC000000000000000000999999000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000CCCC0000FF
      FF0000CCCC00CC660000CC660000CC6600000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC0099999900999999009999990099999900CC666600FFFFFF00FFFFFF00FFCC
      CC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFFFF00FFCCCC00FFFFFF00FFFF
      FF00FFCCCC00FFFFFF00FFFFFF00CC666600999999000000000000000000CCCC
      CC000000000000000000CCCCCC000000000000000000CCCCCC00000000000000
      0000CCCCCC000000000000000000999999000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000CC
      CC00FF990000FF990000CC660000CC6600000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC009999990099999900CC666600FFCCCC00CC666600CC66
      6600FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCCCC00FFCC
      CC00CC666600CC666600FFCCCC00CC66660099999900CCCCCC00999999009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC009999990099999900CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099330000FF990000FF990000CC6600000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000066666600CCCCCC00CCCCCC0099999900CC666600FFCCCC00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFCCCC00FFCC
      CC00FFCCCC00FFCCCC00FFCCCC00CC66660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0000000000000000000000000000000000CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099330000FF990000FF9900000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066666600CCCCCC00CCCCCC00CC666600CC666600CC666600CC66
      6600CC666600CC666600CC666600CC666600CC666600CC666600CC666600CC66
      6600CC666600CC666600CC666600CC6666009999990099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900999999009999990000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC0066999900666699009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC00B2B2B200999999009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC0066999900666699009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC00B2B2B200999999009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E5000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E5000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E5000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B2000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00F2EABF00CC663300FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC0099999900E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B2000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900F2EABF00F2EABF00FFCC9900FFCC9900CC663300F2EA
      BF00F2EABF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC0099999900CCCC
      CC00E5E5E500E5E5E500CCCCCC00999999000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00CC660000CC663300CC663300CC66
      3300CC663300FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC009999990099999900999999009999
      990099999900CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900F2EABF00F2EABF00FFCC9900FFCC9900CC663300F2EA
      BF00F2EABF00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B2000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00FFFFCC00FFCC9900CC663300FFFF
      CC00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC0099999900CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B2000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E5000000000000000000000000000000
      000000000000E5E5E500CC999900E5E5E500FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E5000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00FFCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900000000000000000000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFCC9900FFCC
      9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900CC99
      6600CC99660099330000000000000000000000000000B2B2B200CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2
      B200B2B2B20099999900000000000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      000000000000000000000000000000000000CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      660099330000CC9966009933000000000000B2B2B200B2B2B200B2B2B200B2B2
      B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2
      B20099999900B2B2B2009999990000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      000000000000000000000000000000000000CC996600FFFFFF00FFCC9900FFCC
      9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC
      9900CC996600993300009933000000000000B2B2B20000000000CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900999999000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      000000000000000000000000000000000000CC996600FFFFFF00FFCC9900FFCC
      9900FFCC9900FFCC990000CC000000990000FFCC99000000FF000000CC00FFCC
      9900CC996600CC9966009933000000000000B2B2B20000000000CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B20099999900CCCCCC00B2B2B20099999900CCCC
      CC00B2B2B200B2B2B200999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC0000000000000000000000000000000000CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC996600CC996600CC99660099330000B2B2B20000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B200B2B2B200B2B2B2009999990099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      990000000000000000000000000000000000CC996600FFFFFF00FFCC9900FFCC
      9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC
      9900CC996600CC996600CC99660099330000B2B2B20000000000CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00B2B2B200B2B2B200B2B2B2009999990099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      99000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600FFCC
      9900FFCC9900CC996600CC9966009933000000000000B2B2B200B2B2B200B2B2
      B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200CCCC
      CC00CCCCCC00B2B2B200B2B2B2009999990099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC99
      6600FFCC9900FFCC9900CC996600993300000000000000000000B2B2B2000000
      000000000000000000000000000000000000000000000000000000000000B2B2
      B200CCCCCC00CCCCCC00B2B2B2009999990099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      990099999900999999009999990000000000000000000000000000000000CC99
      6600FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC99
      6600CC996600CC9966009933000000000000000000000000000000000000B2B2
      B20000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0000000000B2B2
      B200B2B2B200B2B2B200999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      990099999900999999009999990000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC996600000000000000000000000000000000000000000000000000B2B2
      B200000000000000000000000000000000000000000000000000000000000000
      0000B2B2B20000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000CC996600FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500FFFF
      FF00CC9966000000000000000000000000000000000000000000000000000000
      0000B2B2B20000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC000000
      0000B2B2B20000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000CC996600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000000000000000
      0000B2B2B2000000000000000000000000000000000000000000000000000000
      000000000000B2B2B200000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000000000000000
      000000000000B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2
      B200B2B2B200B2B2B200000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000066CCFF003399CC003399CC0066CCFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B2B2B2009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990000000000000000000000000000000000000000003399CC003399
      CC003399CC003399CC003399CC0066CCFF0066CCFF003399CC003399CC003399
      CC003399CC003399CC0000000000000000000000000000000000999999009999
      9900999999009999990099999900B2B2B200B2B2B20099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000000000003399CC0099FF
      FF00FFFFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0066CCFF0066CC
      FF0066CCFF003399CC000000000000000000000000000000000099999900CCCC
      CC00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2B200B2B2
      B200B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000003399
      CC0099FFFF00FFFFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0066CC
      FF003399CC000000000000000000000000000000000000000000000000009999
      9900CCCCCC00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2
      B200999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00003399CC0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      990000000000000000000000000000000000CC996600CC996600CC996600CC99
      6600CC996600CC996600CC99660000000000000000003399CC00006699000066
      9900006699000066990000669900006699009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      00003399CC0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      990000000000000000000000000000000000CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      00003399CC0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      990000000000000000000000000000000000CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      00003399CC00FFFFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      990000000000000000000000000000000000CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000066CCFF0066CCFF00FFFFFF0000FFFF0000FFFF0000FFFF0066CCFF0066CC
      FF00000000000000000000000000000000000000000000000000000000000000
      0000B2B2B200B2B2B200FFFFFF00CCCCCC00CCCCCC00CCCCCC00B2B2B200B2B2
      B20000000000000000000000000000000000CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000003399CC0099FFFF00FFFFFF0000FFFF0000FFFF003399CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00FFFFFF00CCCCCC00CCCCCC00999999000000
      000000000000000000000000000000000000CC996600FFFFFF00FFFFFF00CC99
      6600CC996600CC996600CC99660000000000000000003399CC0099FFFF0099FF
      FF003399CC003399CC003399CC003399CC009999990000000000000000009999
      9900999999009999990099999900000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999000000000000000000000000000000
      000000000000000000003399CC003399CC003399CC003399CC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900999999009999990099999900000000000000
      000000000000000000000000000000000000CC996600FFFFFF00FFFFFF00CC99
      6600E5E5E500CC9966000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC00CCFFFF0000669900000000009999990000000000000000009999
      9900E5E5E5009999990000000000000000000000000099999900CCCCCC00CCCC
      CC0099999900CCCCCC0099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CC996600FFFFFF00FFFFFF00CC99
      6600CC996600000000000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC000066990000000000000000009999990000000000000000009999
      9900999999000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CC996600CC996600CC996600CC99
      660000000000000000000000000000000000000000003399CC003399CC003399
      CC003399CC000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      00009999CC0000008000000080000000800000008000000080009999CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCCC009999990099999900999999009999990099999900CCCCCC000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      80000000CC000000FF000000FF000000FF000000FF000000FF000000CC000000
      8000000000000000000000000000000000000000000000000000000000009999
      9900B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2B2009999
      990000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000080000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF0000008000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC0099999900000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0000000000000000009999990000000000000080000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000800000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00999999000000000000000000000099000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966009999990000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999009999CC000000CC000000FF000000
      FF00FFFFFF00FFFFFF000000FF000000FF000000FF00FFFFFF00FFFFFF000000
      FF000000FF000000CC009999CC0000000000CCCCCC00B2B2B200CCCCCC00CCCC
      CC00FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00FFFFFF00FFFFFF00CCCC
      CC00CCCCCC00B2B2B200CCCCCC00000000000000CC000000990000000000CC99
      6600FFFFFF009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC996600B2B2B20099999900000000009999
      9900000000009999990099999900999999009999990099999900999999009999
      990099999900999999000000000099999900000080000000FF000000FF000000
      FF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF000000
      FF000000FF000000FF00000080000000000099999900CCCCCC00CCCCCC00CCCC
      CC00FFFFFF00FFFFFF00FFFFFF00CCCCCC00FFFFFF00FFFFFF00FFFFFF00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000FF000000CC0000009900CC99
      6600FFFFFF0099330000CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC996600CCCCCC00B2B2B200999999009999
      99000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00999999000000000099999900000080000000FF000000FF000000
      FF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000
      FF000000FF000000FF00000080000000000099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000FF000000CC0000000000CC99
      6600FFFFFF009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC996600CCCCCC00B2B2B200000000009999
      9900000000009999990099999900999999009999990099999900999999009999
      990099999900999999000000000099999900000080000000FF000000FF000000
      FF000000FF000000FF00FFFFFF00FFFFFF00FFFFFF000000FF000000FF000000
      FF000000FF000000FF00000080000000000099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00FFFFFF00FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000FF000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC996600CCCCCC0000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900000080000000FF000000FF000000
      FF000000FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000FF000000
      FF000000FF000000FF00000080000000000099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC009999990000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00000000000000000099999900000080000000FF000000FF000000
      FF00FFFFFF00FFFFFF00FFFFFF000000FF00FFFFFF00FFFFFF00FFFFFF000000
      FF000000FF000000FF00000080000000000099999900CCCCCC00CCCCCC00CCCC
      CC00FFFFFF00FFFFFF00FFFFFF00CCCCCC00FFFFFF00FFFFFF00FFFFFF00CCCC
      CC00CCCCCC00CCCCCC009999990000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999009999CC000000CC000000FF000000
      FF00FFFFFF00FFFFFF000000FF000000FF000000FF00FFFFFF00FFFFFF000000
      FF000000FF000000CC009999CC0000000000CCCCCC00B2B2B200CCCCCC00CCCC
      CC00FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00FFFFFF00FFFFFF00CCCC
      CC00CCCCCC00B2B2B200CCCCCC0000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0000000000000000009999990000000000000080000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000800000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00999999000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000080000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF0000008000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC0099999900000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC000000000000000000999999000000000000000000000000000000
      80000000CC000000FF000000FF000000FF000000FF000000FF000000CC000000
      8000000000000000000000000000000000000000000000000000000000009999
      9900B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2B2009999
      990000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      00009999CC0000008000000080000000800000008000000080009999CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCCC009999990099999900999999009999990099999900CCCCCC000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000000000000000000000000
      0000000000000000000000000000999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000000000000CCCCCC00000000000000000000000000000000000000
      0000000000000000000000000000CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      00000000000000000000000000009999990000000000000000003333CC000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000006699000066
      9900006699000066990000669900CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      00000000000000000000000000009999990000000000000000003333CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      0000000000000000FF000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CCCCCC000000000000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000003333
      CC000066FF000000CC0000000000000000000000000000000000000000000000
      00000000FF000000000000000000000000000000000000000000000000009999
      9900E5E5E5009999990000000000000000000000000000000000000000000000
      0000CCCCCC00000000000000000000000000000000003399CC00CCFFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      00000000CC000000FF0000009900000000000000000000000000000000000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC009999990000000000000000000000000000000000CCCC
      CC0099999900000000000000000000000000000000003399CC0099FFFF00CCFF
      FF0099FFFF0099FFFF0099FFFF00CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000FF000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000CCCCCC009999
      990000000000000000000000000000000000000000003399CC00CCFFFF0099FF
      FF00CCFFFF0099FFFF0099FFFF00CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000FF00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC0099999900CCCCCC00999999000000
      000000000000000000000000000000000000000000003399CC0099FFFF00CCFF
      FF0099FFFF00CCFFFF0099FFFF00CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC996600CC996600CC996600CC9966000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000999999009999990099999900999999000000000000000000000000000000
      00000000000000000000000000000000CC000000FF0000009900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC0099999900000000000000
      000000000000000000000000000000000000000000003399CC00CCFFFF0099FF
      FF00CCFFFF0099FFFF00CCFFFF00CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC996600E5E5E500CC996600000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000999999000000000099999900000000000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000CC00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC009999990099999900999999000000
      000000000000000000000000000000000000000000003399CC0099FFFF00CCFF
      FF0099FFFF00CCFFFF0099FFFF00CC996600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC996600CC99660000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000CC000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000999999009999
      990000000000000000000000000000000000000000003399CC00CCFFFF0099FF
      FF00CCFFFF0099FFFF00CCFFFF00CC996600CC996600CC996600CC996600CC99
      6600CC9966000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      CC000000FF000000FF0000009900000000000000000000000000000000000000
      CC00000099000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000009999
      990099999900000000000000000000000000000000003399CC00CCFFFF00CCFF
      FF0099FFFF00CCFFFF0099FFFF00CCFFFF0099FFFF00CCFFFF0099FFFF0099FF
      FF00006699000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC009999990000000000000000000000000000000000000000000000CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      00000000CC00000099000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      000099999900999999000000000000000000000000003399CC00CCFFFF00CCFF
      FF00CC6600009933000099330000993300009933000099330000CCFFFF0099FF
      FF00006699000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999009999990099999900CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000666699000000
      CC00666699000000000000000000000000000000000000000000000000000000
      000000000000000000000000CC00000000000000000000000000CCCCCC009999
      9900CCCCCC000000000000000000000000000000000000000000000000000000
      000000000000000000009999990000000000000000003399CC00CCFFFF00CCFF
      FF00CC660000FFFFFF00FF990000FF990000FF9900009933000099FFFF00CCFF
      FF00006699000000000000000000000000000000000099999900CCCCCC00CCCC
      CC0099999900FFFFFF00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003399CC003399
      CC003399CC00CC660000FFFFFF00FF990000993300003399CC003399CC003399
      CC00000000000000000000000000000000000000000000000000999999009999
      99009999990099999900FFFFFF00CCCCCC009999990099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000CC660000CC6600000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900999999000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000B00000000100010000000000800500000000000000000000
      000000000000000000000000FFFFFF00FCFFFCFF00000000F87FF87F00000000
      F07FF07F00000000E07FE07F00000000C03FC03F00000000803E803E00000000
      001C001C00000000000800080000000000010001000000008003800300000000
      8007800700000000800F800F00000000C01FC01F00000000E03FE03F00000000
      F07FF07F00000000F8FFF8FF00000000FFFFFFFF80008000C003C0038000BF7E
      C003C0038000BF7AC003C0038000BF00C003C0038000BF7EC003C0038000BD7A
      C003C00380008000C003C0038000BF7EC003C0038000BF7EC003C0038000BD7A
      C003C00380008000C003C0038000BF7EC007C0078000BF7EC00FC00F8000BF7E
      C01FC01F8000BD7AFFFFFFFF800080008FFF8FFFFFFFFFFF07FF07FFC001C001
      83FF83FF8001800181FF81FF80018001C0FFC0FF80018001E003E00380018001
      F001F00180018001F800F80080018001F800F80080018001F800F80080018001
      F800F80080018001F800F80080018001F800F80080018001F800F80080018001
      FC01FC0180018001FE03FE03FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC003C003
      80038003C003DFFB80038003C003D00B80038003C003DFFB80038003C003D00B
      80038003C003DFFBFFFFFFFFC003D00BBFFBBFFBC003DFFBFFFFFFFFC003D00B
      BFFBBFFBC003DFFBFFFFFFFFC003D043BFFBBFFBC007DFD7FFFFFFFFC00FDFCF
      AAABAAABC01FC01FFFFFFFFFFFFFFFFFFFFFFFFFFFF8FFF8EFFDEFFD80008000
      C7FFC7FF8000BFE0C3FBC3FB8001A001E3F7E3F78003BC03F1E7F1E78007A007
      F8CFF8CF8007BC07FC1FFC1F8007A007FE3FFE3F8007BE07FC1FFC1F8007A007
      F8CFF8CF8007BFF7E1E7E1E78007A087C3F3C3F3800FBF8FC7FDC7FD801FBF9F
      FFFFFFFF803F803FFFFFFFFFFFFFFFFFA7FFA7FFFFFFFFFF01FF01FF00000000
      007F007F00006DB6003F003F00006DB6001F001F00000000500F500F00006DB6
      F007F00700006DB6F803F80300000000FC01FC0100006DB6FE00FE0000006DB6
      FF00FF0000000000FF80FF8000006DB6FFC0FFC000006DB6FFE0FFE000000000
      FFF0FFF0000003C0FFF8FFF8000000008FFF8FFF8FFF8FFF07FF07FF07FF07FF
      83FF83FF83FF83FF81FF81FF81FF81FFC0FFC0FFC0FFC0FFE003E003E003E003
      F001F001F001F001F800F800F800F800F800F800F800F800F800F800F800F800
      F800F800F800F800F800F800F800F800F800F800F800F800F800F800F800F800
      FC01FC01FC01FC01FE03FE03FE03FE03FFFFFFFFFDFFFDFFC007C007E0FFE8FF
      80038003801FA05F00010001001F803F00014001001F001F00014001000F000F
      00007FF0000F000F00004000000F000F8000800000010001C000DFE001010001
      E001E82101010001E007EFF7000F000FF007F417008F000FF003F7FB00AF002F
      F803F803803F803FFFFFFFFFE1FFE1FFFFFFFFFFFFFFFFFFFFFFFFFFFFDFFFDF
      FFFFFFFFFFCFFFCFFC3FFC3FE007E007C003C003FFCFFFCFC003C003FFDFFFDF
      E007E007FFFFFFFFF00FF00F01800180F00FF00F01807D80F00FF00F01807D80
      F00FF00F01807D80F00FF00F01807D80F81FF81F01806180FC3FFC3F03816381
      FFFFFFFF07836783FFFFFFFF0F870F87FFFFFFFFE000E000F01FF01FE000EFFE
      E00FE00FE000EFFEC007C007E000EC068003800360006FFE0001000120002802
      000100010000080200010001200028020001000160006FFE00010001E000EC06
      00010001E000EFFE00010001E000EC0680038003E000EFFEC007C007E000EC06
      E00FE00FE000EFFEF01FF01FE000E000FFFFFFFFFE00FE00EFFDEFFDFE00FEFE
      C7FFC7FFC000C0FEC3FBC3FB800080FEE3F7E3F7800080FEF1E7F1E7800080FE
      F8CFF8CF800080FEFC1FFC1F800080F0FE3FFE3F800180F5FC1FFC1F800380F3
      F8CFF8CF80078007E1E7E1E780078007C3F3C3F380078007C7FDC7FD80078007
      FFFFFFFFC00FC00FFFFFFFFFFCFFFCFF00000000000000000000000000000000
      000000000000}
  end
  object pm: TPopupMenu
    Left = 128
    Top = 272
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
    object N7: TMenuItem
      Caption = #20316'  '#32773
      OnClick = N7Click
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 664
    Top = 328
    object N11: TMenuItem
      Caption = #26684#24335
      OnClick = N11Click
    end
    object N21: TMenuItem
      Caption = #26684#24335
      OnClick = N21Click
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 584
    Top = 344
    object N12: TMenuItem
      Caption = #26684#24335'1'
      OnClick = N12Click
    end
    object N22: TMenuItem
      Caption = #26684#24335'2'
      OnClick = N22Click
    end
  end
  object bearsaledataset: TADODataSet
    CommandText = 
      'select value from SYS_BSSET where name = '#39'bear'#39' or name = '#39'pxtui' +
      'huoamount'#39#13#10'order by name'
    Parameters = <>
    Left = 568
    Top = 392
  end
  object query: TADOQuery
    Parameters = <>
    Left = 648
    Top = 400
  end
  object selectmenu: TPopupMenu
    Left = 608
    Top = 272
    object N5: TMenuItem
      Caption = #21333#36873
    end
    object N6: TMenuItem
      Caption = #20840#36873
      OnClick = N6Click
    end
    object N8: TMenuItem
      Caption = #21382#21490#26126#32454
      OnClick = N8Click
    end
  end
  object ds2: TDataSource
    DataSet = aq2
    Left = 232
    Top = 368
  end
  object aq2: TADOQuery
    Parameters = <>
    Left = 928
    Top = 408
  end
  object dsheader: TDataSource
    DataSet = aqheader
    Left = 464
    Top = 376
  end
  object aqheader: TADOQuery
    Parameters = <>
    Left = 552
    Top = 120
  end
  object savedlg: TSaveDialog
    Left = 712
    Top = 304
  end
end
