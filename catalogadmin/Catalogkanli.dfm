object frmCatalogkanli: TfrmCatalogkanli
  Left = 0
  Top = 0
  Caption = #22270#20070#21697#30446#31649#29702
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
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 17
  object RzToolButton4: TRzToolButton
    Left = 739
    Top = 0
    Width = 55
    Height = 36
    Hint = 'Exit'
    DisabledIndex = 3
    GradientColorStyle = gcsSystem
    ImageIndex = 2
    Layout = blGlyphTop
    ShowCaption = True
    UseToolbarButtonSize = False
    UseToolbarShowCaption = False
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
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 1012
    Height = 40
    AutoResize = False
    AutoStyle = False
    TopMargin = -2
    RowHeight = 40
    ButtonLayout = blGlyphTop
    ButtonWidth = 60
    ButtonHeight = 40
    ShowButtonCaptions = True
    TextOptions = ttoShowTextLabels
    BorderColor = clWhite
    BorderInner = fsFlatRounded
    BorderOuter = fsNone
    BorderSides = [sdTop, sdBottom]
    BorderWidth = 0
    Color = 16113353
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    GradientColorStyle = gcsCustom
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnView
      BtnNew
      BtnSave
      btncnacelsave
      BtnClear
      BtnCancel
      BtnUndo
      BtnDelete
      BtnImport
      BtnExport
      BtnJumptoLine
      RzToolButton1
      BtnAlignClient
      BtnAlignBottom
      BtnExit)
    object BtnSave: TRzToolButton
      Left = 104
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Save'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      Layout = blGlyphTop
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20445#23384#13'[F4]'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnSaveClick
    end
    object BtnExit: TRzToolButton
      Left = 734
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      Layout = blGlyphTop
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
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
    object BtnNew: TRzToolButton
      Left = 54
      Top = 0
      Width = 50
      Height = 36
      Hint = 'New'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #28155#21152#13'[F2]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnNewClick
    end
    object BtnImport: TRzToolButton
      Left = 404
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Import'
      DisabledIndex = 9
      GradientColorStyle = gcsSystem
      ImageIndex = 8
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20837#13'[F7]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnImportClick
    end
    object BtnExport: TRzToolButton
      Left = 454
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Export'
      DisabledIndex = 11
      GradientColorStyle = gcsSystem
      ImageIndex = 10
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'[F6]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnExportClick
    end
    object BtnDelete: TRzToolButton
      Left = 354
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Delete'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21024#38500#13'[F8]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnDeleteClick
    end
    object BtnClear: TRzToolButton
      Left = 204
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Clear'
      DisabledIndex = 17
      GradientColorStyle = gcsSystem
      ImageIndex = 16
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20462#25913#13'[F5]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnClearClick
    end
    object BtnCancel: TRzToolButton
      Left = 254
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Cancel'
      DisabledIndex = 21
      GradientColorStyle = gcsSystem
      ImageIndex = 20
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #20316#24223#13'[F9]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnCancelClick
    end
    object BtnView: TRzToolButton
      Left = 4
      Top = 0
      Width = 50
      Height = 36
      Hint = 'View'
      DisabledIndex = 23
      GradientColorStyle = gcsSystem
      ImageIndex = 22
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#35810#13'(&F)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnViewClick
    end
    object BtnJumptoLine: TRzToolButton
      Left = 504
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Jump to Line'
      DisabledIndex = 27
      GradientColorStyle = gcsSystem
      ImageIndex = 26
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #32479#19968#13'[F3]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnJumptoLineClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 684
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 29
      GradientColorStyle = gcsSystem
      ImageIndex = 28
      Layout = blGlyphTop
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
    object BtnAlignClient: TRzToolButton
      Left = 619
      Top = 0
      Width = 65
      Height = 36
      Hint = 'Align Client'
      DisabledIndex = 31
      GradientColorStyle = gcsSystem
      ImageIndex = 30
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21512#24182#37325#20070'[F10]'
      OnClick = BtnAlignClientClick
    end
    object BtnUndo: TRzToolButton
      Left = 304
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Undo'
      DisabledIndex = 33
      GradientColorStyle = gcsSystem
      ImageIndex = 32
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #21462#28040#13#20316#24223
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnUndoClick
    end
    object RzToolButton1: TRzToolButton
      Left = 554
      Top = 0
      Width = 65
      Height = 36
      Hint = 'Align Client'
      DisabledIndex = 31
      GradientColorStyle = gcsSystem
      ImageIndex = 30
      Layout = blGlyphTop
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #38468#21152#26465#30721#13#25171#21360
      OnClick = RzToolButton1Click
    end
    object btncnacelsave: TRzToolButton
      Left = 154
      Top = 0
      Width = 50
      Height = 36
      Hint = 'Save'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      Layout = blGlyphTop
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25764#28040#13'[F11]'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = btncnacelsaveClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 40
    Width = 1012
    Height = 202
    Align = alClient
    BevelOuter = bvNone
    ParentBackground = False
    TabOrder = 1
    object Label8: TLabel
      Left = 808
      Top = 10
      Width = 36
      Height = 17
      Caption = #24635#21697#31181
    end
    object rzcbinput: TRzCheckBox
      Left = 20
      Top = 9
      Width = 71
      Height = 19
      BiDiMode = bdLeftToRight
      Caption = ' '#36830#32493#24405#20837
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      State = cbUnchecked
      TabOrder = 0
    end
    object GroupBox1: TGroupBox
      Left = 0
      Top = 32
      Width = 1012
      Height = 164
      Enabled = False
      TabOrder = 1
      object Label22: TLabel
        Left = 469
        Top = 136
        Width = 24
        Height = 17
        Caption = #23383#25968
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label34: TLabel
        Left = 663
        Top = 136
        Width = 24
        Height = 17
        Caption = #21360#24352
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label35: TLabel
        Left = 850
        Top = 15
        Width = 48
        Height = 17
        Caption = #20869#23481#31616#20171
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 16
        Top = 15
        Width = 24
        Height = 17
        Caption = #26465#30721
      end
      object Label2: TLabel
        Left = 218
        Top = 15
        Width = 29
        Height = 17
        Caption = 'ISBN'
      end
      object SpeedButton1: TSpeedButton
        Left = 379
        Top = 12
        Width = 28
        Height = 24
        Caption = '10'
        Flat = True
        OnClick = SpeedButton1Click
      end
      object Label3: TLabel
        Left = 16
        Top = 44
        Width = 24
        Height = 17
        Caption = #20070#21517
        Font.Charset = ANSI_CHARSET
        Font.Color = clRed
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label4: TLabel
        Left = 16
        Top = 73
        Width = 24
        Height = 17
        Caption = #23450#20215
        Font.Charset = ANSI_CHARSET
        Font.Color = clRed
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label5: TLabel
        Left = 168
        Top = 73
        Width = 24
        Height = 17
        Caption = #20316#32773
      end
      object Label6: TLabel
        Left = 18
        Top = 104
        Width = 24
        Height = 17
        Caption = #31867#21035
      end
      object Label7: TLabel
        Left = 211
        Top = 104
        Width = 36
        Height = 17
        Caption = #20986#29256#31038
      end
      object Label11: TLabel
        Left = 16
        Top = 136
        Width = 48
        Height = 17
        Caption = #20986#29256#26085#26399
      end
      object Label13: TLabel
        Left = 223
        Top = 136
        Width = 24
        Height = 17
        Caption = #29256#27425
      end
      object btaddtype: TSpeedButton
        Left = 179
        Top = 101
        Width = 23
        Height = 25
        Caption = #26032
        Flat = True
        OnClick = btaddtypeClick
      end
      object btaddpress: TSpeedButton
        Left = 410
        Top = 101
        Width = 25
        Height = 25
        Caption = #26032
        Flat = True
        OnClick = btaddpressClick
      end
      object Label17: TLabel
        Left = 319
        Top = 73
        Width = 29
        Height = 17
        Caption = #20876'/'#21253
      end
      object Label14: TLabel
        Left = 469
        Top = 44
        Width = 24
        Height = 17
        Caption = #21360#27425
      end
      object Label12: TLabel
        Left = 663
        Top = 104
        Width = 24
        Height = 17
        Caption = #35013#24103
      end
      object Label15: TLabel
        Left = 469
        Top = 73
        Width = 24
        Height = 17
        Caption = #19995#20070
      end
      object Label16: TLabel
        Left = 469
        Top = 104
        Width = 24
        Height = 17
        Caption = #24320#26412
      end
      object Label19: TLabel
        Left = 440
        Top = 15
        Width = 53
        Height = 17
        Caption = 'ISBN'#20998#31867
      end
      object Label20: TLabel
        Left = 663
        Top = 44
        Width = 24
        Height = 17
        Caption = #38468#20214
      end
      object Label10: TLabel
        Left = 663
        Top = 15
        Width = 24
        Height = 17
        Caption = #35793#32773
      end
      object Label23: TLabel
        Left = 608
        Top = 44
        Width = 12
        Height = 17
        Caption = #27425
      end
      object Label24: TLabel
        Left = 534
        Top = 44
        Width = 12
        Height = 17
        Caption = #31532
      end
      object Label21: TLabel
        Left = 639
        Top = 73
        Width = 48
        Height = 17
        Caption = #33719#22870#24773#20917
      end
      object spselectType: TSpeedButton
        Left = 155
        Top = 101
        Width = 25
        Height = 25
        Flat = True
        Glyph.Data = {
          36040000424D3604000000000000360000002800000010000000100000000100
          2000000000000004000000000000000000000000000000000000FF00FF00CCCC
          CC00C0C0C000E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCCCC006699
          99006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0066CC
          FF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCC
          FF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
          FF00CCCCFF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
          FF00FF00FF00CCCCFF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC99
          9900CC999900CC999900CCCC9900E5E5E500FF00FF00FF00FF00FF00FF00FF00
          FF00FF00FF00FF00FF00CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EA
          BF00FFFFCC00F2EABF00F2EABF00CC999900ECC6D900FF00FF00FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900FFCC9900FFFFCC00FFFF
          CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00CC999900E5E5E500FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFCC00F2EABF00FFFF
          CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00F2EABF00CCCC9900FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00CCCC9900FFCC9900F2EABF00F2EABF00FFFF
          CC00FFFFCC00FFFFCC00FFFFFF00FFFFFF00F2EABF00CC999900FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00CC999900F2EABF00F2EABF00F2EABF00F2EA
          BF00FFFFCC00FFFFCC00FFFFCC00FFFFCC00FFFFCC00CC999900FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00CCCC9900F2EABF00FFFFCC00F2EABF00F2EA
          BF00F2EABF00FFFFCC00FFFFCC00FFFFCC00F2EABF00CC999900FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EA
          BF00F2EABF00F2EABF00F2EABF00FFFFCC00CCCC9900CCCC9900FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900ECC6D900FFFFFF00FFFF
          CC00F2EABF00F2EABF00F2EABF00FFCC9900CC999900E5E5E500FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FF00FF00FFCCCC00CC999900FFCCCC00F2EA
          BF00F2EABF00F2EABF00CCCC9900CC999900FFCCCC00FF00FF00FF00FF00FF00
          FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00E5E5E500CCCC9900CC99
          9900CC999900CC999900CC999900E5E5E500FF00FF00FF00FF00}
        OnClick = spselectTypeClick
      end
      object mcontent: TMemo
        Left = 849
        Top = 42
        Width = 153
        Height = 114
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 0
        OnKeyDown = mcontentKeyDown
      end
      object meditwords: TEdit
        Left = 499
        Top = 133
        Width = 121
        Height = 23
        Alignment = taRightJustify
        Ctl3D = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        NumbersOnly = True
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 1
        Text = '0'
        OnKeyDown = meditwordsKeyDown
      end
      object medityinzhang: TEdit
        Left = 692
        Top = 133
        Width = 130
        Height = 23
        Ctl3D = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 2
        OnKeyDown = medityinzhangKeyDown
      end
      object editcode: TEdit
        Left = 48
        Top = 13
        Width = 147
        Height = 23
        Ctl3D = False
        MaxLength = 13
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 3
        OnKeyPress = editcodeKeyPress
      end
      object editisbn: TEdit
        Left = 254
        Top = 13
        Width = 126
        Height = 23
        Ctl3D = False
        MaxLength = 13
        ParentCtl3D = False
        TabOrder = 4
        OnKeyPress = editisbnKeyPress
      end
      object editbookname: TEdit
        Left = 48
        Top = 42
        Width = 289
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 5
        OnKeyPress = editbooknameKeyPress
      end
      object editbookself: TEdit
        Left = 336
        Top = 42
        Width = 71
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 6
        OnKeyPress = editbookselfKeyPress
      end
      object editprice: TEdit
        Left = 48
        Top = 71
        Width = 79
        Height = 23
        Alignment = taRightJustify
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 7
        Text = #65509'0.00'
        OnKeyPress = editpriceKeyPress
      end
      object editauthor: TEdit
        Left = 197
        Top = 71
        Width = 80
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 8
        OnKeyPress = editauthorKeyPress
      end
      object rcbpress: TComboBox
        Left = 291
        Top = 101
        Width = 116
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 9
        OnKeyPress = rcbpressKeyPress
      end
      object datapressday: TDateTimePicker
        Left = 76
        Top = 133
        Width = 110
        Height = 25
        Date = 40146.605024768520000000
        Time = 40146.605024768520000000
        TabOrder = 10
        OnKeyPress = datapressdayKeyPress
      end
      object edquery: TEdit
        Left = 254
        Top = 101
        Width = 38
        Height = 25
        AutoSize = False
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 11
        OnKeyPress = edqueryKeyPress
      end
      object edpresscount: TEdit
        Left = 254
        Top = 133
        Width = 153
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 12
        OnKeyDown = edpresscountKeyDown
      end
      object spepack: TRzSpinEdit
        Left = 352
        Top = 71
        Width = 56
        Height = 23
        AllowKeyEdit = True
        Max = 10000.000000000000000000
        Value = 1.000000000000000000
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 13
        OnKeyPress = spepackKeyPress
      end
      object edISBNtype: TEdit
        Left = 499
        Top = 13
        Width = 121
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 14
        OnKeyPress = edISBNtypeKeyPress
      end
      object edbook: TEdit
        Left = 499
        Top = 71
        Width = 121
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 15
        OnKeyPress = edbookKeyPress
      end
      object edaffix: TEdit
        Left = 692
        Top = 42
        Width = 130
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 16
        OnKeyPress = edaffixKeyPress
      end
      object edyizhe: TEdit
        Left = 692
        Top = 13
        Width = 130
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 17
        OnKeyPress = edyizheKeyPress
      end
      object cbformat: TComboBox
        Left = 499
        Top = 101
        Width = 121
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 18
        OnKeyPress = cbformatKeyPress
        Items.Strings = (
          '16'#24320
          '32'#24320
          '48'#24320
          '64'#24320
          #22823'16'#24320
          #22823'32'#24320
          #22823'48'#24320
          #22823'64'#24320)
      end
      object cbbind: TComboBox
        Left = 692
        Top = 101
        Width = 130
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 19
        OnKeyPress = cbbindKeyPress
        Items.Strings = (
          #31934#35013
          #24179#35013
          #31616#35013)
      end
      object edprintcount: TRzSpinEdit
        Left = 550
        Top = 42
        Width = 56
        Height = 23
        AllowKeyEdit = True
        Value = 1.000000000000000000
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 20
        OnKeyPress = edprintcountKeyPress
      end
      object edhuojiangstate: TEdit
        Left = 692
        Top = 71
        Width = 130
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 21
        OnKeyDown = edhuojiangstateKeyDown
      end
      object edtypequery: TEdit
        Left = 48
        Top = 101
        Width = 40
        Height = 25
        AutoSize = False
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 22
        OnKeyPress = edtypequeryKeyPress
      end
      object edtypename: TEdit
        Left = 87
        Top = 101
        Width = 67
        Height = 25
        AutoSize = False
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 23
        OnKeyPress = edqueryKeyPress
      end
    end
    object RzButton1: TRzButton
      Left = 552
      Top = 6
      Caption = #26174#31034#20840#37096
      TabOrder = 2
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 633
      Top = 6
      Caption = #26174#31034#20316#24223
      TabOrder = 3
      OnClick = RzButton2Click
    end
    object RzButton3: TRzButton
      Left = 719
      Top = 6
      Caption = #26174#31034#19981#20316#24223
      TabOrder = 4
      OnClick = RzButton3Click
    end
    object edpinzhong: TEdit
      Left = 849
      Top = 7
      Width = 153
      Height = 23
      Alignment = taRightJustify
      Ctl3D = False
      Enabled = False
      ParentCtl3D = False
      TabOrder = 5
      Text = '0'
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 242
    Width = 1012
    Height = 470
    Align = alBottom
    Ctl3D = False
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgMultiSelect]
    ParentCtl3D = False
    ParentFont = False
    PopupMenu = pm
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = DBGrid1CellClick
    OnTitleClick = DBGrid1TitleClick
    Columns = <
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'ISBN'
        ReadOnly = True
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
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'barcode'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #26465#30721
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Visible = False
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'name'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 300
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'UserBarcode1'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #26465#30721'('#38468#21152')'
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 100
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'price'
        ReadOnly = True
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
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'abbreviatedname'
        ReadOnly = True
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
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'author'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20316#32773
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 50
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'ID'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Visible = False
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'pid'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Visible = False
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'typename'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #31867#21035
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'userdefcode'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #33258#32534#30721
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Pdate'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#26085#26399
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 70
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'PressCount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 35
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'ISBNType'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = 'ISBN'#20998#31867
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 60
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Yizhe'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #35793#32773
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 50
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Printcount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #21360#27425
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 35
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Affix'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #38468#20214
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 80
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Bookformat'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #24320#26412
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 50
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Bind'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #35013#24103
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 40
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Collectbook'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #19995#20070
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 70
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'BookWords'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #21253'/'#20876
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 35
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'huojiangstate'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #33719#22870#24773#20917
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 120
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = 'Bk'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'wordscount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #23383#25968
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
        FieldName = 'yinzhang'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #21360#24352
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
        FieldName = 'bcontent'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20869#23481#31616#20171
        Title.Font.Charset = ANSI_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -12
        Title.Font.Name = #24494#36719#38597#40657
        Title.Font.Style = []
        Width = 100
        Visible = True
      end>
  end
  object ImageList1: TImageList
    Left = 560
    Top = 400
    Bitmap = {
      494C010122002300F00010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000009000000001002000000000000090
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
      000000000000000000000000000000000000000000000000000000000000CC99
      6600993300000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300009933000099330000000000000000000000000000000000000000
      000099330000CC99660000000000000000000000000000000000999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      000099999900CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300009933000000000000000000000000000000000000000000000000
      0000000000009933000000000000000000000000000000000000999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300000000000000000000000000000000000000000000000000000000
      0000000000009933000000000000000000000000000000000000999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000009933000000000000000000000000000000000000000000000000
      0000000000009933000000000000000000000000000000000000999999009999
      9900000000009999990000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000099330000993300000000000000000000000000000000
      000099330000CC99660000000000000000000000000000000000999999000000
      0000000000000000000099999900999999000000000000000000000000000000
      000099999900CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009933000099330000993300009933
      0000CC9966000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009999990099999900999999009999
      9900CCCCCC000000000000000000000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
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
      000000000000000000000000000000000000000000000000000000000000CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000009933
      0000993300000000000000000000993300009933000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900999999000000000000000000999999009999990000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000009933
      0000CC660000993300000000000099330000CC66000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00999999000000000099999900CCCCCC0099999900000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC000000000000000000999999000000000000000000000000009933
      0000CC660000CC6600009933000099330000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC009999990099999900CCCCCC00CCCCCC00999999000000
      000000000000000000000000000000000000000099000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966009999990000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000099330000993300009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000099999900999999009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000CC000000990000000000CC99
      6600FFFFFF009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC996600B2B2B20099999900000000009999
      9900000000009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000999999000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC66000099330000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000FF000000CC0000009900CC99
      6600FFFFFF0099330000CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC996600CCCCCC00B2B2B200999999009999
      99000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000999999000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC66000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000FF000000CC0000000000CC99
      6600FFFFFF009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC996600CCCCCC00B2B2B200000000009999
      9900000000009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000999999000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC66000099330000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000FF000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC996600CCCCCC0000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC66000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCC
      CC00CCCCCC00999999000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC000000000000000000999999000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC66000099330000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCC
      CC0099999900000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000099330000993300009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000099999900999999009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      990000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC000000000000000000999999000000000000000000000000009933
      0000CC660000CC6600009933000099330000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC009999990099999900CCCCCC00CCCCCC00999999000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000009933
      0000CC660000993300000000000099330000CC66000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00999999000000000099999900CCCCCC0099999900000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC000000000000000000999999000000000000000000000000009933
      0000993300000000000000000000993300009933000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900999999000000000000000000999999009999990000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300000000000000000000000000000000000000000000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999000000000000000000000000000000000000000000999999009999
      99009999990099999900000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099330000CC66
      0000CC660000CC660000993300000000000099330000CC660000CC660000CC66
      000099330000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00999999000000000099999900CCCCCC00CCCCCC00CCCC
      CC0099999900000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000000000000000000009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      000099330000CC660000CC660000CC660000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E5000000000000000000000000000000
      00000000000099330000CC660000CC660000CC66000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B2000000000000000000000000000000
      000099330000CC660000CC660000CC660000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC00999999000000000000000000000000009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900000000000000000099330000CC66
      0000CC660000CC660000993300000000000099330000CC660000CC660000CC66
      000099330000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00999999000000000099999900CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B2000000000099330000993300009933
      0000993300000000000000000000000000000000000000000000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999000000000000000000000000000000000000000000999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E500000000000000000000000000FFFFFF0000000000FFFF
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
      00000000000000000000000000000000000000000000FF330000FF330000FF33
      0000FF330000FF330000FF330000FF330000FF330000FF330000FF330000FF33
      0000FF330000FF330000FF330000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900999999009999990000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008080800000009900000099000000990000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008080800066666600666666006666660000000000000000000000
      00000000000000000000000000000000000000000000FF330000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FF330000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009999990000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00808080000000CC0000009900000099000000990000009900000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00808080009999990066666600666666006666660066666600000000000000
      00000000000000000000000000000000000000000000FF330000FFFFFF009999
      9900FFFFFF009999990099999900FFFFFF009999990099999900FFFFFF009999
      990099999900FFFFFF00FF330000000000000000000099999900000000009999
      9900000000009999990099999900000000009999990099999900000000009999
      990099999900000000009999990000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF000000CC000000CC000000CC00000099000000990000009900000099000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00999999009999990099999900666666006666660066666600666666000000
      00000000000000000000000000000000000000000000FF330000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FF330000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009999990000000000FFFFFF0000000000FFFFFF000000
      00000000FF000000CC000000CC000000CC000000990000009900000099000099
      990000000000000000000000000000000000FFFFFF0000000000FFFFFF000000
      0000CCCCCC009999990099999900999999006666660066666600666666006666
      66000000000000000000000000000000000000000000FF330000FFFFFF009999
      9900FFFFFF009999990099999900FFFFFF009999990099999900FFFFFF009999
      990099999900FFFFFF00FF330000000000000000000099999900000000009999
      9900000000009999990099999900000000009999990099999900000000009999
      9900999999000000000099999900000000000000000000000000000000000000
      00000000FF000000FF000000CC000000CC000000CC00000099000099990000CC
      CC00009999000000000000000000000000000000000000000000000000000000
      0000CCCCCC00CCCCCC0099999900999999009999990066666600666666009999
      99006666660000000000000000000000000000000000FF330000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FF330000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000000000000000
      0000000000000000FF000000FF000000CC000000CC000099990000CCCC0000CC
      CC0000CCCC000099990000000000000000000000000000000000000000000000
      000000000000CCCCCC00CCCCCC00999999009999990066666600999999009999
      99009999990066666600000000000000000000000000FF330000FFFFFF00CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600FFFFFF00FF330000000000000000000099999900000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000099999900000000000000000000000000000000000000
      000000000000000000000000FF000000800000CCCC0000FFFF0000FFFF0000CC
      CC0000CCCC0000CCCC0000999900000000000000000000000000000000000000
      00000000000000000000CCCCCC006666660099999900CCCCCC00CCCCCC009999
      99009999990099999900666666000000000000000000FF330000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FF330000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000000000000000
      000000000000000000000000000000CCCC0000FFFF00FFFFFF00C0C0C00000FF
      FF0000CCCC0000CCCC0000CCCC00009999000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC00FFFFFF00C0C0C000CCCC
      CC009999990099999900999999006666660000000000FF330000FFFFFF00FFFF
      FF00FFFFFF009999990099999900FFFFFF009999990099999900FFFFFF009999
      990099999900FFFFFF00FF330000000000000000000099999900000000000000
      0000000000009999990099999900000000009999990099999900000000009999
      9900999999000000000099999900000000000000000000000000000000000000
      00000000000000000000000000000000000000CCCC0000FFFF00FFFFFF00C0C0
      C00000FFFF0000CCCC0000999900993300000000000000000000000000000000
      00000000000000000000000000000000000099999900CCCCCC00FFFFFF00C0C0
      C000CCCCCC0099999900666666006666660000000000FF330000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FF330000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000CCCC0000FFFF00FFFF
      FF0000FFFF0000999900CC660000993300000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00FFFF
      FF00CCCCCC0066666600999999006666660000000000FF330000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FF330000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000CCCC0000FF
      FF0000CCCC00CC660000CC660000CC6600000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC009999990099999900999999009999990000000000FF330000FF330000FF33
      0000FF330000FF330000FF330000FF330000FF330000FF330000FF330000FF33
      0000FF330000FF330000FF330000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000CC
      CC00FF990000FF990000CC660000CC6600000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC00999999009999990000000000FF330000FF330000FF33
      0000FF330000FF330000FF330000FF330000FF330000FF330000FF330000FF33
      0000FF330000FF330000FF330000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099330000FF990000FF990000CC6600000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000066666600CCCCCC00CCCCCC009999990000000000FFCC9900FF330000FF33
      0000FF330000FF330000FF330000FF330000FF330000FF330000FF330000FF33
      0000FF330000FF330000FFCC99000000000000000000CCCCCC00999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900CCCCCC00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099330000FF990000FF9900000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066666600CCCCCC00CCCCCC000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000000000000CCCCCC000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      00000000000000000000000000000000000000000000000000003333CC000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      00000000000000000000000000000000000000000000000000003333CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      0000000000000000FF000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000000000000000000003333
      CC000066FF000000CC0000000000000000000000000000000000000000000000
      00000000FF000000000000000000000000000000000000000000000000009999
      9900E5E5E5009999990000000000000000000000000000000000000000000000
      0000CCCCCC0000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000000000000000000000000
      00000000CC000000FF0000009900000000000000000000000000000000000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC009999990000000000000000000000000000000000CCCC
      CC009999990000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000FF000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000CCCCCC009999
      99000000000000000000000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000FF00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC0099999900CCCCCC00999999000000
      00000000000000000000000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      00000000000000000000000000000000CC000000FF0000009900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC0099999900000000000000
      00000000000000000000000000000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000CC00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC009999990099999900999999000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000CC000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000999999009999
      99000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      CC000000FF000000FF0000009900000000000000000000000000000000000000
      CC00000099000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000009999
      99009999990000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      99000000000000000000000000000000000000000000000000000000CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      00000000CC00000099000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      00009999990099999900000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000000000000666699000000
      CC00666699000000000000000000000000000000000000000000000000000000
      000000000000000000000000CC00000000000000000000000000CCCCCC009999
      9900CCCCCC000000000000000000000000000000000000000000000000000000
      00000000000000000000999999000000000000000000C0C0C000CC996600CC99
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
      0000000000009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900000000000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000993300009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003399CC0000669900006699000066
      99000066990000669900006699000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      990099999900999999009999990099999900CC996600CC996600CC996600CC99
      6600CC996600CC996600CC99660000000000000000003399CC00006699000066
      9900006699000066990000669900006699009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      9900999999009999990099999900999999003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      000000000000000000000000000099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      000000000000000000000000000099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      000000000000000000000000000099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      000000000000000000000000000099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999003399CC0099FFFF0099FFFF003399
      CC003399CC003399CC003399CC000000000000000000CC996600FFFFFF00FFFF
      FF00CC996600CC996600CC996600CC99660099999900CCCCCC00CCCCCC009999
      9900999999009999990099999900000000000000000099999900000000000000
      000099999900999999009999990099999900CC996600FFFFFF00FFFFFF00CC99
      6600CC996600CC996600CC99660000000000000000003399CC0099FFFF0099FF
      FF003399CC003399CC003399CC003399CC009999990000000000000000009999
      9900999999009999990099999900000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999003399CC0099FFFF0099FFFF003399
      CC00CCFFFF0000669900000000000000000000000000CC996600FFFFFF00FFFF
      FF00CC996600E5E5E500CC9966000000000099999900CCCCCC00CCCCCC009999
      9900CCCCCC009999990000000000000000000000000099999900000000000000
      000099999900E5E5E5009999990000000000CC996600FFFFFF00FFFFFF00CC99
      6600E5E5E500CC9966000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC00CCFFFF0000669900000000009999990000000000000000009999
      9900E5E5E5009999990000000000000000000000000099999900CCCCCC00CCCC
      CC0099999900CCCCCC0099999900000000003399CC0099FFFF0099FFFF003399
      CC000066990000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00CC996600CC996600000000000000000099999900CCCCCC00CCCCCC009999
      9900999999000000000000000000000000000000000099999900000000000000
      000099999900999999000000000000000000CC996600FFFFFF00FFFFFF00CC99
      6600CC996600000000000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC000066990000000000000000009999990000000000000000009999
      9900999999000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990000000000000000003399CC003399CC003399CC003399
      CC000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC9966000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      990099999900000000000000000000000000CC996600CC996600CC996600CC99
      660000000000000000000000000000000000000000003399CC003399CC003399
      CC003399CC000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0000000000999999009999
      99009999990099999900000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5
      E500CC9966000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000999999000000
      00009999990000000000000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC99
      6600000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00999999000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC9966000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000099330000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900999999009999990000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC00999999000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC009999990000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC00999999000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000993300009933000099330000993300009933000099330000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00999999009999990099999900999999009999990099999900CCCC
      CC00CCCCCC00CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC660000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000099330000CC660000CC66
      0000993300009933000099330000993300009933000099330000993300009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999009999990099999900999999009999
      9900CCCCCC00CCCCCC00999999000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00999999000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000099330000CC6600009933
      0000FFFFFF00993300009933000099330000993300009933000099330000FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00999999009999990099999900999999009999990099999900FFFF
      FF0099999900CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000099330000E5E5E5009933
      0000FFFFFF00993300009933000099330000993300009933000099330000FFFF
      FF00993300009933000099330000000000000000000099999900E5E5E5009999
      9900FFFFFF00999999009999990099999900999999009999990099999900FFFF
      FF009999990099999900999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      9900000000000000000000000000000000000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00999999000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000099330000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900999999000000000000000000C0C0C000CC996600CC99
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
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000900000000100010000000000800400000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000FFFFFFFF00000000
      FFFFFFFF00000000FFFFFFFF00000000FFFFFFFF00000000FFE7FFE700000000
      C1F3C1F300000000C3FBC3FB00000000C7FBC7FB00000000CBFBCBFB00000000
      DCF3DCF300000000FF07FF0700000000FFFFFFFF00000000FFFFFFFF00000000
      FFFFFFFF00000000FFFFFFFF00000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      8003800380038003800380038003800380038003800380038003800380038003
      8003800380038003FFFFFFFF80038003BFFBBFFB80038003FFFFFFFF80038003
      BFFBBFFB80038003FFFFFFFF80038003BFFBBFFB80038003FFFFFFFF80038003
      AAABAAAB80038003FFFFFFFFFFFFFFFFFFFFFFFFE000E000FFFFFFFFE000EFFE
      E67FE67FE000EFFEE23FE23FE000EC06E01FE01F60006FFE800F800F20002802
      800780070000080280038003200028028001800160006FFE80038003E000EC06
      80078007E000EFFE800F800FE000EC06E01FE01FE000EFFEE23FE23FE000EC06
      E67FE67FE000EFFEFFFFFFFFE000E000FFFFFFFF8FFF8FFFFFFFFFFF07FF07FF
      FFFFFFFF83FF83FF87C387C381FF81FF83838383C0FFC0FFC107C107E003E003
      E00FE00FF001F001F01FF01FF800F800F83FF83FF800F800F01FF01FF800F800
      E00FE00FF800F800C107C107F800F80083838383F800F80087C387C3F800F800
      FFFFFFFFFC01FC01FFFFFFFFFE03FE03A7FFA7FFFFFFFFFF01FF01FF80018001
      007F007F8001BFFD003F003F8001A925001F001F8001BFFD500F500F8001A925
      F007F0078001BFFDF803F8038001A005FC01FC018001BFFDFE00FE008001B925
      FF00FF008001BFFDFF80FF808001BFFDFFC0FFC080018001FFE0FFE080018001
      FFF0FFF080018001FFF8FFF8FFFFFFFFFDFFFDFFFFFFFFFFE0FFE8FFEFFDEFFD
      801FA05FC7FFC7FF001F803FC3FBC3FB001F001FE3F7E3F7000F000FF1E7F1E7
      000F000FF8CFF8CF000F000FFC1FFC1F00010001FE3FFE3F01010001FC1FFC1F
      01010001F8CFF8CF000F000FE1E7E1E7008F000FC3F3C3F300AF002FC7FDC7FD
      803F803FFFFFFFFFE1FFE1FFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFBFFFFDFFFDF
      F3FFF3FFFFCFFFCFE007E007E007E007F3FFF3FFFFCFFFCFFBFFFBFFFFDFFFDF
      FFFFFFFFFFFFFFFF0180018001800180018001BE01807D80018001BE01807D80
      018001BE01807D80018001BE01807D80018001B001806180038103B103816381
      078307B3078367830F870F870F870F87FFFFFFFFFFFFFFFF80008000C003C003
      80008000C003DFFB80008000C003D00B80008000C003DFFB80008000C003D00B
      80008000C003DFFB80008000C003D00B80008000C003DFFB80008000C003D00B
      80008000C003DFFB80008000C003D04380008000C007DFD780008000C00FDFCF
      80008000C01FC01F80008000FFFFFFFFFFFFFFFFFDFFFDFFC001C001E0FFE8FF
      80018001801FA05F80018001001F803F80018001001F001F80018001000F000F
      80018001000F000F80018001000F000F80018001000100018001800101010001
      800180010101000180018001000F000F80018001008F000F8001800100AF002F
      80018001803F803FFFFFFFFFE1FFE1FF00000000000000000000000000000000
      000000000000}
  end
  object aquery: TADOQuery
    AutoCalcFields = False
    CacheSize = 3000
    ParamCheck = False
    Parameters = <>
    Prepared = True
    Left = 304
    Top = 448
  end
  object ds: TDataSource
    AutoEdit = False
    DataSet = aquery
    Left = 616
    Top = 440
  end
  object query: TADOQuery
    Parameters = <>
    Left = 744
    Top = 360
  end
  object aqinsert: TADOQuery
    CacheSize = 1000
    LockType = ltBatchOptimistic
    Parameters = <
      item
        Name = '@Type'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@available'
        DataType = ftInteger
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select ID,isbn,name,userdefcode,UserBarcode,case when UserBarcod' +
        'e = Barcode then '#39#39' else UserBarcode end as UserBarcode1,price,b' +
        'arcode,date,Unavailable,type,presscount,bk from bs_bookcatalog w' +
        'here type = :Type'
      'and unavailable =:available')
    Left = 640
    Top = 232
  end
  object dsinsert: TDataSource
    DataSet = aqinsert
    Left = 752
    Top = 280
  end
  object savedlg: TSaveDialog
    Filter = 'CSV'#25991#20214'(*.csv)|*.csv'
    Left = 896
    Top = 200
  end
  object pm: TPopupMenu
    Left = 408
    Top = 392
    object N1: TMenuItem
      Caption = #20840#36873
      OnClick = N1Click
    end
  end
  object frxReport1: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40541.627047083330000000
    ReportOptions.LastChange = 40541.627047083330000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    Left = 432
    Top = 264
    Datasets = <>
    Variables = <>
    Style = <>
  end
end
