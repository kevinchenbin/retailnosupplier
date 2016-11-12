object frmclientdisforbook: Tfrmclientdisforbook
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #23458#25143#25240#25187
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1012
    Height = 712
    Align = alClient
    BevelInner = bvLowered
    TabOrder = 0
    object RzToolbar1: TRzToolbar
      Left = 2
      Top = 2
      Width = 1008
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
      TabOrder = 0
      VisualStyle = vsClassic
      ToolbarControls = (
        BtnSave
        BtnAlignBottom
        BtnExit)
      object BtnExit: TRzToolButton
        Left = 114
        Top = 0
        Width = 55
        Height = 36
        Hint = 'Exit'
        DisabledIndex = 1
        GradientColorStyle = gcsSystem
        ImageIndex = 0
        UseToolbarButtonSize = False
        UseToolbarVisualStyle = False
        VisualStyle = vsGradient
        Caption = #36864#20986#13'(&Q)'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        OnClick = BtnExitClick
      end
      object BtnSave: TRzToolButton
        Left = 4
        Top = 0
        Width = 55
        Height = 36
        Hint = 'Save'
        DisabledIndex = 3
        GradientColorStyle = gcsSystem
        ImageIndex = 2
        UseToolbarButtonSize = False
        UseToolbarVisualStyle = False
        VisualStyle = vsGradient
        Caption = #20445#23384#13'[F4]'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        OnClick = BtnSaveClick
      end
      object BtnAlignBottom: TRzToolButton
        Left = 59
        Top = 0
        Width = 55
        Height = 36
        Hint = 'Align Bottom'
        DisabledIndex = 7
        GradientColorStyle = gcsSystem
        ImageIndex = 6
        UseToolbarButtonSize = False
        UseToolbarVisualStyle = False
        VisualStyle = vsGradient
        Caption = #26368#23567#21270#13'(&N)'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        OnClick = BtnAlignBottomClick
      end
    end
    object dbgdiscount: TRzDBGrid
      Left = 457
      Top = 44
      Width = 548
      Height = 652
      Ctl3D = False
      DataSource = ds2
      DefaultDrawing = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentCtl3D = False
      ParentFont = False
      PopupMenu = pmdel
      TabOrder = 1
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnCellClick = dbgdiscountCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'StgID'
          Title.Alignment = taCenter
          Title.Caption = #24215#21495
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -11
          Title.Font.Name = 'Tahoma'
          Title.Font.Style = []
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'clientname'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discount'
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 45
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'dprice'
          Title.Alignment = taCenter
          Title.Caption = #25240#21518#20215#26684
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -12
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 60
          Visible = True
        end>
    end
    object rgbdiscountplan: TRzGroupBox
      Left = 2
      Top = 191
      Width = 447
      Height = 509
      BorderInner = fsBump
      BorderOuter = fsBump
      Caption = #21333#21697#26816#32034
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentColor = True
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
      VisualStyle = vsClassic
      object lblCatalog: TRzLabel
        Left = 16
        Top = 22
        Width = 24
        Height = 17
        Caption = #20070#21495
        DragCursor = crHandPoint
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsUnderline]
        ParentFont = False
        PopupMenu = pm
        OnMouseDown = lblCatalogMouseDown
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object Label7: TLabel
        Left = 16
        Top = 49
        Width = 230
        Height = 17
        Caption = #28201#39336#25552#31034':'#25353'Ctrl'#21487#22810#36873','#21491#38190#20445#23384#36873#20013#30340#21333#21697
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object edtCatalog: TRzEdit
        Left = 72
        Top = 20
        Width = 305
        Height = 23
        Ctl3D = False
        MaxLength = 15
        ParentCtl3D = False
        TabOrder = 0
        OnKeyPress = edtCatalogKeyPress
      end
      object DBGrid1: TDBGrid
        Left = -1
        Top = 72
        Width = 437
        Height = 433
        Ctl3D = False
        DataSource = ds1
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
        ParentCtl3D = False
        ParentFont = False
        PopupMenu = pm1
        TabOrder = 1
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = #24494#36719#38597#40657
        TitleFont.Style = []
        OnCellClick = DBGrid1CellClick
        Columns = <
          item
            Expanded = False
            FieldName = 'ISBN'
            Title.Alignment = taCenter
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 100
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Name'
            Title.Alignment = taCenter
            Title.Caption = #20070#21517
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 200
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Price'
            Title.Alignment = taCenter
            Title.Caption = #23450#20215
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'AbbreviatedName'
            Title.Alignment = taCenter
            Title.Caption = #20986#29256#31038
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'SupplierName'
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 120
            Visible = True
          end>
      end
    end
    object GroupBox2: TGroupBox
      Left = 4
      Top = 135
      Width = 447
      Height = 50
      Caption = #25171#25240#26041#26696#35774#32622
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 3
      object Label4: TLabel
        Left = 12
        Top = 24
        Width = 24
        Height = 17
        Caption = #25240#25187
      end
      object Label9: TLabel
        Left = 217
        Top = 24
        Width = 11
        Height = 17
        Caption = '%'
      end
      object Label6: TLabel
        Left = 258
        Top = 24
        Width = 48
        Height = 17
        Caption = #25240#21518#20215#26684
      end
      object eddiscount: TEdit
        Left = 90
        Top = 22
        Width = 121
        Height = 23
        Alignment = taRightJustify
        BiDiMode = bdLeftToRight
        Ctl3D = False
        MaxLength = 10
        ParentBiDiMode = False
        ParentCtl3D = False
        TabOrder = 0
        OnKeyPress = eddiscountKeyPress
      end
      object edprice: TEdit
        Left = 312
        Top = 22
        Width = 122
        Height = 23
        Alignment = taRightJustify
        BiDiMode = bdLeftToRight
        Ctl3D = False
        MaxLength = 10
        ParentBiDiMode = False
        ParentCtl3D = False
        TabOrder = 1
      end
    end
    object GroupBox1: TGroupBox
      Left = 4
      Top = 44
      Width = 447
      Height = 85
      Caption = #24215#38754#21450#31867#21035#36873#25321
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
      object Label1: TLabel
        Left = 16
        Top = 24
        Width = 24
        Height = 17
        Caption = #24215#21517
      end
      object Label5: TLabel
        Left = 16
        Top = 55
        Width = 24
        Height = 17
        Caption = #23458#25143
      end
      object cbstorage: TComboBox
        Left = 72
        Top = 21
        Width = 305
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 0
        OnSelect = cbstorageSelect
      end
      object cbCusName: TComboBox
        Left = 141
        Top = 51
        Width = 236
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 1
      end
      object edquery: TEdit
        Left = 70
        Top = 51
        Width = 72
        Height = 25
        AutoSize = False
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 2
        OnKeyPress = edqueryKeyPress
      end
    end
  end
  object aqcustom: TADOQuery
    Parameters = <>
    Left = 408
    Top = 72
  end
  object pm: TPopupMenu
    Left = 296
    Top = 32
    object N1: TMenuItem
      Caption = #20070#21495
    end
    object N3: TMenuItem
      Caption = #20070#21517
    end
    object N2: TMenuItem
      Caption = #33258#32534#30721
    end
    object N4: TMenuItem
      Caption = #23450#20215
    end
  end
  object querydetail: TADOQuery
    Parameters = <>
    Left = 952
    Top = 304
  end
  object ds2: TDataSource
    DataSet = querydetail
    Left = 544
    Top = 400
  end
  object query: TADOQuery
    Parameters = <>
    Left = 552
    Top = 336
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 288
    Top = 320
  end
  object ds1: TDataSource
    DataSet = aq
    Left = 160
    Top = 392
  end
  object pm1: TPopupMenu
    Left = 224
    Top = 320
    object N5: TMenuItem
      Caption = #20840#36873
      OnClick = N5Click
    end
    object N7: TMenuItem
      Caption = #20445#23384
      OnClick = N7Click
    end
  end
  object pmdel: TPopupMenu
    Left = 568
    Top = 136
    object MenuItem1: TMenuItem
      Caption = #21024#38500'(&D)'
      OnClick = MenuItem1Click
    end
  end
end
