object frmcheckstock: Tfrmcheckstock
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #23454#24211#30424#28857
  ClientHeight = 712
  ClientWidth = 1012
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  FormStyle = fsMDIChild
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 17
  object Panel1: TPanel
    Left = 0
    Top = 36
    Width = 1012
    Height = 676
    Align = alClient
    BevelOuter = bvNone
    Ctl3D = False
    ParentBackground = False
    ParentColor = True
    ParentCtl3D = False
    TabOrder = 0
    object labpandian: TLabel
      Left = 529
      Top = 7
      Width = 106
      Height = 19
      Caption = '--'#24211#23384#30424#28857
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = #26999#20307
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label9: TLabel
      Left = 423
      Top = 652
      Width = 60
      Height = 17
      Caption = #30424#23384#24635#25968#37327
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 623
      Top = 652
      Width = 60
      Height = 17
      Caption = #30424#23384#24635#30721#27915
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 830
      Top = 652
      Width = 60
      Height = 17
      Caption = #30424#23384#24635#23454#27915
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
    end
    object labtitle: TLabel
      Left = 275
      Top = 7
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
    object GroupBox1: TGroupBox
      Left = 3
      Top = 32
      Width = 1008
      Height = 106
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      object Label4: TLabel
        Left = 7
        Top = 14
        Width = 4
        Height = 17
      end
      object Label6: TLabel
        Left = 20
        Top = 46
        Width = 48
        Height = 17
        Caption = #30424#28857#24211#20301
      end
      object Label7: TLabel
        Left = 561
        Top = 12
        Width = 48
        Height = 17
        Caption = #26412#21333#22791#27880
      end
      object Label15: TLabel
        Left = 415
        Top = 45
        Width = 36
        Height = 17
        Caption = #25805#20316#21592
      end
      object Label16: TLabel
        Left = 244
        Top = 46
        Width = 48
        Height = 17
        Caption = #30424#28857#29366#24577
      end
      object Label17: TLabel
        Left = 23
        Top = 12
        Width = 48
        Height = 17
        Caption = #30424#28857#21333#21495
      end
      object Label14: TLabel
        Left = 561
        Top = 79
        Width = 48
        Height = 17
        Caption = #21333#20070#22791#27880
      end
      object Label13: TLabel
        Left = 427
        Top = 79
        Width = 24
        Height = 17
        Caption = #25439#37327
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label1: TLabel
        Left = 268
        Top = 79
        Width = 24
        Height = 17
        Caption = #25968#37327
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbsearch: TLabel
        Left = 43
        Top = 79
        Width = 24
        Height = 17
        Cursor = crHandPoint
        Alignment = taRightJustify
        Caption = #20070#21495
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
        PopupMenu = pm
        OnMouseDown = lbsearchMouseDown
      end
      object Label2: TLabel
        Left = 244
        Top = 13
        Width = 48
        Height = 17
        Caption = #30424#28857#26085#26399
      end
      object cblocal: TComboBox
        Left = 73
        Top = 43
        Width = 138
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 0
      end
      object memnote: TMemo
        Left = 779
        Top = 11
        Width = 222
        Height = 42
        BorderStyle = bsNone
        Font.Charset = ANSI_CHARSET
        Font.Color = clRed
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        Lines.Strings = (
          #25552#31034#65306#33509#30424#28857#27491#22312#36827#34892#65292#24211#20301#23558#34987#38145#23450#65292
          '            '#20219#20309#23545#35813#24211#20301#30340#25805#20316#37117#23558#31105#27490#12290)
        ParentColor = True
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object membk: TMemo
        Left = 615
        Top = 10
        Width = 162
        Height = 52
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 1
        OnExit = membkExit
      end
      object editusername: TEdit
        Left = 454
        Top = 43
        Width = 68
        Height = 23
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        TabOrder = 3
      end
      object editstate: TEdit
        Left = 296
        Top = 44
        Width = 96
        Height = 23
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        TabOrder = 4
      end
      object editnum: TEdit
        Left = 73
        Top = 10
        Width = 138
        Height = 23
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 5
      end
      object edbk: TEdit
        Left = 615
        Top = 77
        Width = 372
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 6
        OnKeyPress = edbkKeyPress
      end
      object edsamount: TEdit
        Left = 454
        Top = 77
        Width = 68
        Height = 23
        Alignment = taRightJustify
        Ctl3D = False
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 7
        OnKeyPress = edsamountKeyPress
      end
      object edtnumber: TEdit
        Left = 296
        Top = 77
        Width = 96
        Height = 23
        Alignment = taRightJustify
        Ctl3D = False
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 8
        OnExit = edtnumberExit
        OnKeyPress = edtnumberKeyPress
      end
      object edtcheckinfo: TEdit
        Left = 73
        Top = 77
        Width = 138
        Height = 23
        Ctl3D = False
        MaxLength = 13
        ParentCtl3D = False
        TabOrder = 9
        OnKeyPress = edtcheckinfoKeyPress
      end
      object dtpstart: TDateTimePicker
        Left = 296
        Top = 9
        Width = 96
        Height = 25
        Date = 40458.683318182870000000
        Time = 40458.683318182870000000
        TabOrder = 10
      end
    end
    object RzDBNumericEdit1: TRzDBNumericEdit
      Left = 491
      Top = 649
      Width = 91
      Height = 23
      DataSource = dsheader
      DataField = 'totalamount'
      ReadOnly = True
      Alignment = taLeftJustify
      Color = clInfoBk
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      DisplayFormat = '###,###,##0'
    end
    object RzDBNumericEdit2: TRzDBNumericEdit
      Left = 690
      Top = 649
      Width = 87
      Height = 23
      DataSource = dsheader
      DataField = 'Fixedprice'
      ReadOnly = True
      Alignment = taLeftJustify
      Color = clInfoBk
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      DisplayFormat = #65509'###,###,##0.0'
    end
    object RzDBNumericEdit4: TRzDBNumericEdit
      Left = 896
      Top = 649
      Width = 94
      Height = 23
      DataSource = dsheader
      DataField = 'Discountprice'
      ReadOnly = True
      Alignment = taLeftJustify
      Color = clInfoBk
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      DisplayFormat = #65509'###,###,##0.0'
    end
    object dgcheck: TDBGrid
      Left = 3
      Top = 146
      Width = 1008
      Height = 497
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
      TabOrder = 4
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnCellClick = dgcheckCellClick
      Columns = <
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'xuhao'
          Title.Alignment = taCenter
          Title.Caption = #24207#21495
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
          FieldName = 'Barcode'
          Title.Alignment = taCenter
          Title.Caption = #26465#30721
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'BookName'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 200
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
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discount'
          Title.Alignment = taCenter
          Title.Caption = #25240#25187'%'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Fixedprice'
          Title.Alignment = taCenter
          Title.Caption = #30424#23384#30721#27915
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discountprice'
          Title.Alignment = taCenter
          Title.Caption = #30424#23384#23454#27915
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ShouldAmount'
          Title.Alignment = taCenter
          Title.Caption = #30424#28857#25968
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'damagenum'
          Title.Alignment = taCenter
          Title.Caption = #25439#37327
          Width = 35
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Balance'
          Title.Alignment = taCenter
          Title.Caption = #30408#20111#25968
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ActualAmount'
          Title.Alignment = taCenter
          Title.Caption = #30424#21069#24211#23384
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ShouldAmount'
          Title.Alignment = taCenter
          Title.Caption = #30424#21518#24211#23384
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'state1'
          Title.Alignment = taCenter
          Title.Caption = #29366#24577
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'bk'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'STK_BookInfoID'
          Title.Alignment = taCenter
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'NoteCode'
          Title.Alignment = taCenter
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'UserDefCode'
          Title.Alignment = taCenter
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'bkcatalogid'
          Title.Alignment = taCenter
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'id'
          Visible = False
        end>
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 1012
    Height = 36
    AutoResize = False
    AutoStyle = False
    TopMargin = 6
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsFlatRounded
    BorderOuter = fsNone
    BorderSides = [sdTop, sdBottom]
    BorderWidth = 0
    Color = 16113353
    GradientColorStyle = gcsMSOffice
    TabOrder = 1
    VisualStyle = vsClassic
    ToolbarControls = (
      Btninit
      BtnProperties
      BtnViewList
      BtnViewIcons
      BtnHorizontalTile
      BtnChangeOptions
      BtnExport
      RzSpacer1
      RzToolButton2
      RzToolButton1
      RzSpacer2
      BtnPrint
      BtnClear
      BtnAlignBottom
      BtnExit)
    object BtnExit: TRzToolButton
      Left = 720
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 11
      GradientColorStyle = gcsSystem
      ImageIndex = 10
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
    object BtnPrint: TRzToolButton
      Left = 570
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Print'
      DisabledIndex = 13
      GradientColorStyle = gcsSystem
      ImageIndex = 12
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25171#21360#13'[F10]'
      Visible = False
      OnClick = BtnPrintClick
    end
    object Btninit: TRzToolButton
      Left = 4
      Top = 0
      Width = 70
      Height = 36
      Hint = 'Tile'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #30424#28857#21021#22987#21270#13'[F1]'
      OnClick = BtninitClick
    end
    object BtnViewList: TRzToolButton
      Left = 134
      Top = 0
      Width = 80
      Height = 36
      Hint = 'View List'
      DisabledIndex = 17
      GradientColorStyle = gcsSystem
      ImageIndex = 16
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #30424#28857#20462#25913#24211#23384#13'[F3]'
      OnClick = BtnViewListClick
    end
    object BtnViewIcons: TRzToolButton
      Left = 214
      Top = 0
      Width = 60
      Height = 36
      Hint = 'View Icons'
      DisabledIndex = 19
      GradientColorStyle = gcsSystem
      ImageIndex = 18
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #32467#26463#30424#28857#13'[F4]'
      Enabled = False
      OnClick = BtnViewIconsClick
    end
    object BtnHorizontalTile: TRzToolButton
      Left = 274
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Horizontal Tile'
      DisabledIndex = 21
      GradientColorStyle = gcsSystem
      ImageIndex = 20
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26410#30424#20070#13'[F5]'
      Enabled = False
      OnClick = BtnHorizontalTileClick
    end
    object BtnExport: TRzToolButton
      Left = 404
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Export'
      DisabledIndex = 23
      GradientColorStyle = gcsSystem
      ImageIndex = 22
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'[F8]'
      OnClick = BtnExportClick
    end
    object BtnClear: TRzToolButton
      Left = 620
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Clear'
      DisabledIndex = 29
      GradientColorStyle = gcsSystem
      ImageIndex = 28
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #39044#35272#13'[F11]'
      Visible = False
      OnClick = BtnClearClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 670
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 31
      GradientColorStyle = gcsSystem
      ImageIndex = 30
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26368#23567#21270#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
    object BtnProperties: TRzToolButton
      Left = 74
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Properties'
      DisabledIndex = 33
      GradientColorStyle = gcsSystem
      ImageIndex = 32
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #24320#22987#30424#28857'[F2]'
      OnClick = BtnPropertiesClick
    end
    object BtnChangeOptions: TRzToolButton
      Left = 324
      Top = 0
      Width = 80
      Height = 36
      Hint = 'Change Options'
      DisabledIndex = 35
      GradientColorStyle = gcsSystem
      ImageIndex = 34
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #32467#26463#26412#27425#30424#28857'[F6]'
      OnClick = BtnChangeOptionsClick
    end
    object RzToolButton1: TRzToolButton
      Left = 512
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Export'
      DisabledIndex = 23
      GradientColorStyle = gcsSystem
      ImageIndex = 22
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #30424#28857#22120#23548#20837
      OnClick = RzToolButton1Click
    end
    object RzToolButton2: TRzToolButton
      Left = 462
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Export'
      DisabledIndex = 23
      GradientColorStyle = gcsSystem
      ImageIndex = 22
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #30424#28857#22120#23548#20986
      OnClick = RzToolButton2Click
    end
    object RzSpacer1: TRzSpacer
      Left = 454
      Top = 6
      Grooved = True
    end
    object RzSpacer2: TRzSpacer
      Left = 562
      Top = 6
      Grooved = True
    end
  end
  object pm: TPopupMenu
    AutoPopup = False
    Left = 96
    Top = 264
    object N1: TMenuItem
      Caption = #20070#21495
      OnClick = N1Click
    end
    object N4: TMenuItem
      Caption = #33258#32534#30721' '
      OnClick = N4Click
    end
    object N2: TMenuItem
      Caption = #20070#21517
      OnClick = N2Click
    end
    object N5: TMenuItem
      Caption = #23450#20215
      OnClick = N5Click
    end
    object N3: TMenuItem
      Caption = #20316#32773
      OnClick = N3Click
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 376
    Top = 272
  end
  object atable: TADOTable
    LockType = ltBatchOptimistic
    TableName = 'STK_StockInventories'
    Left = 272
    Top = 328
  end
  object ds: TDataSource
    DataSet = aqueryupdate
    Left = 336
    Top = 328
  end
  object adosp: TADOStoredProc
    Parameters = <>
    Left = 288
    Top = 280
  end
  object aqueryupdate: TADOQuery
    CursorType = ctStatic
    LockType = ltBatchOptimistic
    Parameters = <
      item
        Name = 'stocknum'
        DataType = ftString
        Size = 15
        Value = Null
      end>
    SQL.Strings = (
      
        'select RANK() OVER(order by STK_StockInventories.id ) as xuhao, ' +
        'STK_StockInventories .*,'
      
        'case STK_StockInventories.states when 0 then '#39#30424#28857#20013#39' else '#39#24050#30830#35748#39' en' +
        'd as state1,'
      
        'BS_BookCatalog.UserDefCode,BS_BookCatalog.Author from STK_StockI' +
        'nventories  '
      
        'left join STK_BookInfo on STK_StockInventories.STK_BookInfoID= S' +
        'TK_BookInfo.id '
      
        'left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_BookCa' +
        'talog .id '
      'where STK_StockInventories.NoteCode = :stocknum')
    Left = 168
    Top = 312
  end
  object adocount: TADOQuery
    Parameters = <>
    Left = 232
    Top = 256
  end
  object aquerynotcheckbook: TADOQuery
    Parameters = <>
    Left = 424
    Top = 224
  end
  object RvProject1: TRvProject
    Engine = RvSystem1
    Left = 504
    Top = 336
  end
  object rvt: TRvDataSetConnection
    FieldAliasList.Strings = (
      '')
    RuntimeVisibility = rtDeveloper
    DataSet = aqueryupdate
    Left = 560
    Top = 312
  end
  object RvSystem1: TRvSystem
    TitleSetup = 'Output Options'
    TitleStatus = 'Report Status'
    TitlePreview = 'Report Preview'
    SystemFiler.StatusFormat = 'Generating page %p'
    SystemPreview.ZoomFactor = 100.000000000000000000
    SystemPrinter.ScaleX = 100.000000000000000000
    SystemPrinter.ScaleY = 100.000000000000000000
    SystemPrinter.StatusFormat = 'Printing page %p'
    SystemPrinter.Title = 'Rave Report'
    SystemPrinter.UnitsFactor = 1.000000000000000000
    Left = 464
    Top = 392
  end
  object dsheader: TDataSource
    DataSet = aqheader
    Left = 824
    Top = 376
  end
  object aqheader: TADOQuery
    Parameters = <>
    Left = 848
    Top = 480
  end
  object savedlg: TSaveDialog
    Filter = 'CSV'#25991#20214'(*.CSV)|*.csv'
    Left = 648
    Top = 272
  end
  object fcon: TADOConnection
    LoginPrompt = False
    Left = 520
    Top = 280
  end
  object xlsconnect: TADOConnection
    LoginPrompt = False
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 432
    Top = 312
  end
  object aqinput: TADOQuery
    Parameters = <>
    Left = 824
    Top = 256
  end
  object aqinsertkuchen: TADOQuery
    Parameters = <>
    Left = 104
    Top = 272
  end
  object opfile: TOpenDialog
    Filter = 'Excel|*.xls'
    Left = 320
    Top = 488
  end
end
