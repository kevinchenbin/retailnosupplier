object frmmemberorder: Tfrmmemberorder
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #20250#21592#35746#38405
  ClientHeight = 718
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1012
    Height = 718
    Align = alClient
    BevelInner = bvLowered
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 0
    object Label3: TLabel
      Left = 458
      Top = 689
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
    object rztlbr1: TRzToolbar
      Left = 2
      Top = 2
      Width = 1008
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
      TabOrder = 0
      VisualStyle = vsClassic
      ToolbarControls = (
        tlbtn8
        BtnNew
        tlbtn1
        RzToolButton1
        tlbtn2
        tlbtn3
        BtnAttachFiles
        RzToolButton2
        BtnPrint
        BtnView
        BtnAlignBottom
        tlbtn7)
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
        Caption = #26597#21333#13'[F1]'
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
        OnClick = tlbtn1Click
      end
      object tlbtn2: TRzToolButton
        Tag = 5
        Left = 221
        Top = 0
        Width = 55
        Height = 36
        GradientColorStyle = gcsSystem
        ImageIndex = 8
        UseToolbarButtonSize = False
        UseToolbarVisualStyle = False
        VisualStyle = vsGradient
        Caption = #21024#34892#13'[F5]'
        OnClick = tlbtn2Click
      end
      object tlbtn3: TRzToolButton
        Tag = 6
        Left = 276
        Top = 0
        Width = 55
        Height = 36
        GradientColorStyle = gcsSystem
        ImageIndex = 10
        UseToolbarButtonSize = False
        UseToolbarVisualStyle = False
        VisualStyle = vsGradient
        Caption = #32479#19968#13'[F6]'
        OnClick = tlbtn3Click
      end
      object tlbtn7: TRzToolButton
        Left = 631
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
        Caption = #22686#21333#13'[F2]'
        OnClick = BtnNewClick
      end
      object BtnView: TRzToolButton
        Left = 511
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
        Caption = #26597#20070#13'(F&)'
        OnClick = BtnViewClick
      end
      object BtnAttachFiles: TRzToolButton
        Left = 331
        Top = 0
        Width = 70
        Height = 36
        Hint = 'Attach Files'
        DisabledIndex = 25
        GradientColorStyle = gcsSystem
        ImageIndex = 24
        UseToolbarButtonSize = False
        UseToolbarVisualStyle = False
        VisualStyle = vsGradient
        Caption = #20250#21592#36164#26009'[F7]'
        OnClick = BtnAttachFilesClick
      end
      object BtnAlignBottom: TRzToolButton
        Left = 571
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
        Left = 456
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
        OnClick = BtnPrintClick
      end
      object RzToolButton1: TRzToolButton
        Tag = 3
        Left = 166
        Top = 0
        Width = 55
        Height = 36
        GradientColorStyle = gcsSystem
        ImageIndex = 2
        UseToolbarButtonSize = False
        UseToolbarVisualStyle = False
        VisualStyle = vsGradient
        Caption = #20462#25913#13'[F4]'
        Enabled = False
        OnClick = RzToolButton1Click
      end
      object RzToolButton2: TRzToolButton
        Left = 401
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
        Caption = #39044#35272#13'[F11]'
        OnClick = RzToolButton2Click
      end
    end
    object grpbxNtHeader: TGroupBox
      Left = 2
      Top = 38
      Width = 1008
      Height = 155
      Align = alTop
      Caption = #35746#38405#20250#21592
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      object lbl2: TRzLabel
        Left = 342
        Top = 21
        Width = 45
        Height = 17
        Alignment = taRightJustify
        Caption = #21345#21495'[F4]'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl4: TRzLabel
        Left = 564
        Top = 21
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
      object RzButton1: TSpeedButton
        Left = 509
        Top = 19
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
      object RzLabel3: TRzLabel
        Left = 366
        Top = 51
        Width = 24
        Height = 17
        Caption = #22995#21517
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel8: TRzLabel
        Left = 363
        Top = 79
        Width = 24
        Height = 17
        Caption = #31867#21035
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel9: TRzLabel
        Left = 543
        Top = 49
        Width = 48
        Height = 17
        Caption = #21345#20869#20313#39069
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel11: TRzLabel
        Left = 552
        Top = 79
        Width = 36
        Height = 17
        Caption = #24635#31215#20998
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel12: TRzLabel
        Left = 721
        Top = 50
        Width = 36
        Height = 17
        Caption = #24635#28040#36153
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel13: TRzLabel
        Left = 721
        Top = 78
        Width = 36
        Height = 17
        Caption = #26377#25928#26399
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object Label1: TLabel
        Left = 266
        Top = 108
        Width = 13
        Height = 19
        Caption = '%'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -14
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbl8: TRzLabel
        Left = 23
        Top = 108
        Width = 46
        Height = 19
        Caption = #25968#37327'[&S]'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -14
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl9: TRzLabel
        Left = 143
        Top = 108
        Width = 49
        Height = 19
        Caption = #25240#25187'[&D]'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -14
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lblCatalog: TRzLabel
        Left = 27
        Top = 39
        Width = 38
        Height = 26
        Alignment = taRightJustify
        Caption = #20070#21495
        DragCursor = crHandPoint
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -19
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
        OnMouseDown = lblCatalogMouseDown
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object Label2: TLabel
        Left = 880
        Top = 21
        Width = 24
        Height = 17
        Caption = #22791#27880
      end
      object Label4: TLabel
        Left = 362
        Top = 110
        Width = 24
        Height = 17
        Caption = #35746#37329
      end
      object dbedtRetailNtCode: TRzDBEdit
        Left = 594
        Top = 18
        Width = 110
        Height = 23
        DataSource = dsourceheader
        DataField = 'MemberNtCode'
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
        TabOrder = 0
      end
      object edname: TEdit
        Left = 393
        Top = 48
        Width = 110
        Height = 23
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 1
      end
      object edyue: TEdit
        Left = 594
        Top = 47
        Width = 110
        Height = 23
        BiDiMode = bdRightToLeft
        Ctl3D = False
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentBiDiMode = False
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object dbhd: TDBNavigator
        Left = 704
        Top = 18
        Width = 132
        Height = 23
        DataSource = dsourceheader
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
        Flat = True
        TabOrder = 3
        OnClick = dbhdClick
      end
      object edcard: TEdit
        Left = 393
        Top = 19
        Width = 110
        Height = 23
        Ctl3D = False
        MaxLength = 13
        ParentCtl3D = False
        TabOrder = 4
        OnKeyPress = edcardKeyPress
      end
      object edtype: TEdit
        Left = 393
        Top = 77
        Width = 110
        Height = 23
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 5
      end
      object edjifen: TEdit
        Left = 594
        Top = 77
        Width = 110
        Height = 23
        Alignment = taRightJustify
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 6
      end
      object edTotalConsumption: TEdit
        Left = 763
        Top = 47
        Width = 110
        Height = 23
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 7
      end
      object edyouxiaodate: TEdit
        Left = 763
        Top = 77
        Width = 110
        Height = 23
        Ctl3D = False
        Enabled = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 8
      end
      object edtCatalog: TRzEdit
        Left = 71
        Top = 37
        Width = 187
        Height = 31
        Ctl3D = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -19
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        MaxLength = 20
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 9
        OnKeyPress = edtCatalogKeyPress
      end
      object chdingwei: TCheckBox
        Left = 295
        Top = 61
        Width = 49
        Height = 17
        Caption = #23450#20301
        TabOrder = 10
        Visible = False
      end
      object numorder: TRzNumericEdit
        Left = 392
        Top = 106
        Width = 111
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 11
        OnKeyPress = numorderKeyPress
        IntegersOnly = False
        DisplayFormat = '##0.00'
      end
      object dbnbedtAmount: TEdit
        Left = 75
        Top = 106
        Width = 65
        Height = 23
        Alignment = taRightJustify
        Ctl3D = False
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 12
        Text = '0'
        OnKeyPress = dbnbedtAmountKeyPress
      end
      object dbnbedtDiscount: TEdit
        Left = 193
        Top = 106
        Width = 65
        Height = 23
        Alignment = taRightJustify
        Ctl3D = False
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 13
        Text = '100'
        OnKeyPress = dbnbedtDiscountKeyPress
      end
      object membk: TMemo
        Left = 879
        Top = 44
        Width = 117
        Height = 85
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 14
      end
    end
    object dbgrdNote: TRzDBGrid
      Left = 3
      Top = 199
      Width = 1012
      Height = 482
      Ctl3D = False
      DataSource = ds
      DefaultDrawing = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ParentCtl3D = False
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnCellClick = dbgrdNoteCellClick
      DisabledColor = cl3DLight
      FixedLineColor = clDefault
      LineColor = clBtnShadow
      AltRowShadingFixed = False
      Columns = <
        item
          Alignment = taCenter
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
          FieldName = 'catalogname'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 300
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
          FieldName = 'price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'amount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'discount'
          Title.Alignment = taCenter
          Title.Caption = #25240#25187'%'
          Width = 65
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
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'id'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'bkcatalogid'
          Visible = False
        end>
    end
    object Edit1: TEdit
      Left = 580
      Top = 683
      Width = 70
      Height = 23
      Alignment = taRightJustify
      AutoSelect = False
      AutoSize = False
      Ctl3D = False
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
    object Edit2: TRzNumericEdit
      Left = 689
      Top = 683
      Width = 70
      Height = 23
      Ctl3D = False
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
      DisplayFormat = '##0.00'
    end
    object Edit3: TRzNumericEdit
      Left = 765
      Top = 683
      Width = 70
      Height = 23
      Ctl3D = False
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      ReadOnly = True
      TabOrder = 5
      DisplayFormat = '##0.00'
    end
  end
  object adocon: TADOConnection
    Left = 464
    Top = 352
  end
  object ds: TDataSource
    DataSet = adoaqnote
    Left = 64
    Top = 280
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 360
    Top = 352
  end
  object dsourceheader: TDataSource
    DataSet = aqheader
    Left = 328
    Top = 272
  end
  object adosp: TADOStoredProc
    MaxRecords = 1
    ProcedureName = 'InsertNewMemberOrder'
    Parameters = <
      item
        Name = '@stgid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@Operator'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@memoberid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@OrderMoney'
        DataType = ftFloat
        Value = Null
      end
      item
        Name = '@Remarks'
        DataType = ftString
        Size = -1
        Value = Null
      end>
    Left = 400
    Top = 336
  end
  object adoaqnote: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'HeaderID'
        Attributes = [paSigned, paNullable]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      'select distinct RANK() OVER(order by A.ID desc) as xuhao,'
      
        'a.id,a.amount,a.discount,a.FixedPrice,a.DiscountedPrice,a.Member' +
        'OrderHeaderId,a.bkcatalogid,b.name as catalogname,b.Barcode,b.IS' +
        'BN,b.UserDefCode,b.price,b.author,c.AbbreviatedName '
      'from dbo.BS_MemberOrderNote a join dbo.BS_BookCatalog b'
      'on a.bkcatalogid = b.id'
      'left join dbo.BS_PressInfo c'
      'on b.PressID = c.id'
      'where a.MemberorderHeaderID=:HeaderID')
    Left = 552
    Top = 384
  end
  object pm: TPopupMenu
    Left = 104
    Top = 320
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
  object aqheader: TADOQuery
    Parameters = <>
    Left = 584
    Top = 296
  end
  object frxmemberorder: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41260.586706284700000000
    ReportOptions.LastChange = 41260.750965312500000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      ''
      'begin'
      ''
      'end.')
    StoreInDFM = False
    OnGetValue = frxmemberorderGetValue
    Left = 328
    Top = 232
  end
  object frxdetail: TfrxDBDataset
    UserName = 'frxdetail'
    CloseDataSource = False
    DataSet = adoaqnote
    Left = 520
    Top = 464
  end
end
