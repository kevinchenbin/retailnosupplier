object frmReturnStock: TfrmReturnStock
  Left = 0
  Top = 0
  Cursor = crDrag
  Caption = #26410#21160#24211#23384#21450#26234#33021#36864#36135
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
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 17
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
    GradientColorStyle = gcsCustom
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnView
      RzToolButton1
      BtnFastForward
      BtnLastRecord
      BtnAlignBottom
      BtnExit)
    object BtnView: TRzToolButton
      Left = 4
      Top = 0
      Width = 60
      Height = 36
      Hint = 'View'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#35810#13'[F1]'
      OnClick = BtnViewClick
    end
    object BtnFastForward: TRzToolButton
      Left = 124
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Fast Forward'
      DisabledIndex = 3
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36890#30693#21508#24215#13'[F3]'
      OnClick = BtnFastForwardClick
    end
    object BtnExit: TRzToolButton
      Left = 304
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 5
      GradientColorStyle = gcsSystem
      ImageIndex = 4
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
    object BtnLastRecord: TRzToolButton
      Left = 184
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Last Record'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #29983#25104#36864#36135#21333'[F4]'
      OnClick = BtnLastRecordClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 244
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 9
      GradientColorStyle = gcsSystem
      ImageIndex = 8
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26368#23567#21270#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
    object RzToolButton1: TRzToolButton
      Left = 64
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Fast Forward'
      DisabledIndex = 3
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'[F2]'
      OnClick = RzToolButton1Click
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 179
    Width = 1012
    Height = 533
    Align = alBottom
    Ctl3D = False
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ParentCtl3D = False
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 1
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnTitleClick = DBGrid1TitleClick
    Columns = <
      item
        Expanded = False
        FieldName = 'xuhao'
        ReadOnly = True
        Title.Caption = #24207#21495
        Width = 30
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'suppliername'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20379#24212#21830
        Width = 120
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ISBN'
        ReadOnly = True
        Title.Alignment = taCenter
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'bookname'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'price'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'author'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20316#32773
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'AbbreviatedName'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#31038
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'pressdate'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#26085#26399
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'typename'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #31867#21035
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'mayang'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #30721#27915
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'shiyang'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #23454#27915
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'returndate'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #36864#36135#26085#26399
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'lsamount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #38646#21806#25968#37327
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'wsamount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #21457#36135#25968#37327
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'totalamount'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #24635#38144#21806#25968#37327
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'state'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #29366#24577
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        ReadOnly = True
        Visible = False
      end
      item
        Expanded = False
        FieldName = 'id'
        Visible = False
      end>
  end
  object pc: TPageControl
    Left = 0
    Top = 37
    Width = 1012
    Height = 131
    ParentCustomHint = False
    ActivePage = Tab1
    BiDiMode = bdLeftToRight
    DoubleBuffered = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentBiDiMode = False
    ParentDoubleBuffered = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    Style = tsButtons
    TabOrder = 2
    OnChange = pcChange
    object Tab1: TTabSheet
      Caption = #26410#21160#24211#23384#20998#26512
      object Label6: TLabel
        Left = 190
        Top = 11
        Width = 20
        Height = 17
        Caption = '----'
      end
      object Label7: TLabel
        Left = 190
        Top = 42
        Width = 20
        Height = 17
        Caption = '----'
      end
      object Label8: TLabel
        Left = 190
        Top = 73
        Width = 20
        Height = 17
        Caption = '----'
      end
      object dtpstart: TDateTimePicker
        Left = 88
        Top = 7
        Width = 98
        Height = 25
        Date = 40093.449149120370000000
        Time = 40093.449149120370000000
        TabOrder = 0
        OnChange = dtpstartChange
      end
      object dtpend: TDateTimePicker
        Left = 216
        Top = 7
        Width = 98
        Height = 25
        Date = 40093.449270648150000000
        Time = 40093.449270648150000000
        TabOrder = 1
        OnChange = dtpstartChange
      end
      object chrktime: TRzCheckBox
        Left = 16
        Top = 10
        Width = 67
        Height = 19
        Caption = #20837#24211#26102#38388
        State = cbUnchecked
        TabOrder = 2
      end
      object edbook: TEdit
        Left = 398
        Top = 7
        Width = 111
        Height = 25
        AutoSize = False
        Ctl3D = False
        MaxLength = 13
        ParentCtl3D = False
        TabOrder = 3
        OnChange = edbookChange
      end
      object cbtype1: TComboBox
        Left = 607
        Top = 38
        Width = 143
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 4
        OnChange = cbtype1Change
      end
      object cbsupplier: TComboBox
        Left = 664
        Top = 69
        Width = 319
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 5
        OnChange = cbsupplierChange
      end
      object cbstate1: TComboBox
        Left = 840
        Top = 7
        Width = 143
        Height = 25
        BevelKind = bkFlat
        Style = csDropDownList
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 6
        OnChange = cbstate1Change
        Items.Strings = (
          #26080
          #24453#36890#30693
          #24050#36890#30693
          #30830#35748#36864#36135
          #24050#35843#22238)
      end
      object cbstorage1: TComboBox
        Left = 840
        Top = 38
        Width = 143
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 7
      end
      object chstorage: TCheckBox
        Left = 785
        Top = 42
        Width = 49
        Height = 17
        Caption = #24215#21517
        Checked = True
        State = cbChecked
        TabOrder = 8
      end
      object chisbn: TCheckBox
        Left = 351
        Top = 11
        Width = 44
        Height = 17
        Caption = #20070#21495
        TabOrder = 9
      end
      object edname: TEdit
        Left = 607
        Top = 7
        Width = 143
        Height = 25
        AutoSize = False
        Ctl3D = False
        MaxLength = 13
        ParentCtl3D = False
        TabOrder = 10
        OnChange = ednameChange
      end
      object chname: TCheckBox
        Left = 545
        Top = 11
        Width = 51
        Height = 17
        Caption = #20070#21517
        TabOrder = 11
      end
      object chtype: TCheckBox
        Left = 545
        Top = 42
        Width = 49
        Height = 17
        Caption = #31867#21035
        TabOrder = 12
      end
      object chstate1: TCheckBox
        Left = 785
        Top = 11
        Width = 49
        Height = 17
        Caption = #29366#24577
        TabOrder = 13
      end
      object chsupplier: TCheckBox
        Left = 545
        Top = 73
        Width = 60
        Height = 17
        Caption = #20379#24212#21830
        TabOrder = 14
      end
      object edsupplier: TEdit
        Left = 607
        Top = 69
        Width = 58
        Height = 25
        AutoSize = False
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 15
        OnKeyPress = edsupplierKeyPress
      end
      object dtpls1: TDateTimePicker
        Left = 88
        Top = 38
        Width = 98
        Height = 25
        Date = 40093.449149120370000000
        Time = 40093.449149120370000000
        TabOrder = 16
        OnChange = dtpls1Change
      end
      object dtpls2: TDateTimePicker
        Left = 216
        Top = 38
        Width = 98
        Height = 25
        Date = 40093.449270648150000000
        Time = 40093.449270648150000000
        TabOrder = 17
        OnChange = dtpls1Change
      end
      object chlstime: TRzCheckBox
        Left = 16
        Top = 41
        Width = 67
        Height = 19
        Caption = #38646#21806#26102#38388
        State = cbUnchecked
        TabOrder = 18
      end
      object dtp3: TDateTimePicker
        Left = 88
        Top = 69
        Width = 98
        Height = 25
        Date = 40093.449149120370000000
        Time = 40093.449149120370000000
        TabOrder = 19
        OnChange = dtp3Change
      end
      object dtp4: TDateTimePicker
        Left = 216
        Top = 69
        Width = 98
        Height = 25
        Date = 40093.449270648150000000
        Time = 40093.449270648150000000
        TabOrder = 20
        OnChange = dtp3Change
      end
      object chwstime: TRzCheckBox
        Left = 16
        Top = 72
        Width = 67
        Height = 19
        Caption = #21457#36135#26102#38388
        State = cbUnchecked
        TabOrder = 21
      end
      object chlsnum: TRzCheckBox
        Left = 349
        Top = 41
        Width = 85
        Height = 19
        Caption = #38646#21806#25968#37327'<='
        State = cbUnchecked
        TabOrder = 22
      end
      object edlsnum: TEdit
        Left = 437
        Top = 38
        Width = 72
        Height = 25
        AutoSize = False
        Ctl3D = False
        MaxLength = 13
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 23
        OnChange = edlsnumChange
      end
      object chwsnum: TRzCheckBox
        Left = 349
        Top = 72
        Width = 85
        Height = 19
        Caption = #21457#36135#25968#37327'<='
        State = cbUnchecked
        TabOrder = 24
      end
      object edwsnum: TEdit
        Left = 437
        Top = 69
        Width = 72
        Height = 25
        AutoSize = False
        Ctl3D = False
        MaxLength = 13
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 25
        OnChange = edwsnumChange
      end
    end
    object Tab2: TTabSheet
      Caption = #36864#36135#26597#35810
      ImageIndex = 1
      object Label2: TLabel
        Left = 182
        Top = 6
        Width = 20
        Height = 17
        Caption = '----'
      end
      object Label1: TLabel
        Left = 182
        Top = 38
        Width = 20
        Height = 17
        Caption = '----'
      end
      object Label3: TLabel
        Left = 182
        Top = 68
        Width = 20
        Height = 17
        Caption = '----'
      end
      object Label4: TLabel
        Left = 835
        Top = 69
        Width = 46
        Height = 17
        AutoSize = False
        Caption = #22825
        Visible = False
      end
      object chckbxSupplier: TRzCheckBox
        Left = 333
        Top = 6
        Width = 55
        Height = 19
        Caption = #20379#24212#21830
        State = cbUnchecked
        TabOrder = 0
      end
      object chckbxAmount: TRzCheckBox
        Left = 8
        Top = 68
        Width = 67
        Height = 19
        Caption = #24211#23384#25968#37327
        State = cbUnchecked
        TabOrder = 1
      end
      object chckbxPressCount: TRzCheckBox
        Left = 333
        Top = 36
        Width = 55
        Height = 19
        Caption = #20986#29256#31038
        State = cbUnchecked
        TabOrder = 2
      end
      object chckbxType: TRzCheckBox
        Left = 668
        Top = 7
        Width = 43
        Height = 19
        Caption = #31867#21035
        State = cbUnchecked
        TabOrder = 3
      end
      object chckbxShopNum: TRzCheckBox
        Left = 668
        Top = 37
        Width = 43
        Height = 19
        Caption = #24215#21495
        Checked = True
        ReadOnly = True
        State = cbChecked
        TabOrder = 4
      end
      object edtSupplier1: TRzEdit
        Left = 414
        Top = 3
        Width = 51
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 5
        OnKeyPress = edtSupplier1KeyPress
      end
      object edtPressCount1: TRzEdit
        Left = 414
        Top = 34
        Width = 51
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 6
        OnKeyPress = edtPressCount1KeyPress
      end
      object edtSupplier2: TRzDBLookupComboBox
        Left = 464
        Top = 3
        Width = 182
        Height = 23
        Ctl3D = False
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        KeyField = 'ID'
        ListField = 'Name'
        ListSource = dssupplier
        ParentCtl3D = False
        TabOrder = 7
        OnClick = edtSupplier2Click
        AutoDropDown = True
      end
      object edtPress2: TRzDBLookupComboBox
        Left = 464
        Top = 34
        Width = 182
        Height = 23
        Ctl3D = False
        DropDownRows = 20
        KeyField = 'ID'
        ListField = 'AbbreviatedName'
        ListSource = dspress
        ParentCtl3D = False
        TabOrder = 8
        OnClick = edtPress2Click
      end
      object edtAmountLow: TEdit
        Left = 80
        Top = 65
        Width = 98
        Height = 25
        AutoSize = False
        Ctl3D = False
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 9
        OnChange = edtAmountLowChange
        OnKeyPress = edtAmountLowKeyPress
      end
      object chbackdate: TCheckBox
        Left = 7
        Top = 42
        Width = 67
        Height = 17
        Caption = #36864#36135#26085#26399
        TabOrder = 10
      end
      object dtp1: TDateTimePicker
        Left = 80
        Top = 34
        Width = 98
        Height = 25
        Date = 40688.625694965270000000
        Time = 40688.625694965270000000
        TabOrder = 11
        OnChange = dtp1Change
      end
      object dtp2: TDateTimePicker
        Left = 208
        Top = 34
        Width = 98
        Height = 25
        Date = 40688.625694965270000000
        Time = 40688.625694965270000000
        TabOrder = 12
        OnChange = dtp2Change
      end
      object edtAmountHigh: TEdit
        Left = 208
        Top = 65
        Width = 98
        Height = 25
        AutoSize = False
        Ctl3D = False
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 13
        OnKeyPress = edtAmountHighKeyPress
      end
      object chstate: TRzCheckBox
        Left = 855
        Top = 6
        Width = 43
        Height = 19
        Caption = #29366#24577
        State = cbUnchecked
        TabOrder = 14
      end
      object cbstate2: TComboBox
        Left = 904
        Top = 3
        Width = 80
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 15
        OnChange = cbstate2Change
        Items.Strings = (
          #26080
          #24453#36890#30693
          #24050#36890#30693
          #30830#35748#36864#36135
          #24050#35843#22238)
      end
      object cbstorage: TComboBox
        Left = 765
        Top = 34
        Width = 219
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 16
      end
      object cbtype: TComboBox
        Left = 765
        Top = 3
        Width = 64
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        ItemHeight = 17
        ParentCtl3D = False
        TabOrder = 17
        OnChange = cbtypeChange
      end
      object dtprk1: TDateTimePicker
        Left = 80
        Top = 3
        Width = 98
        Height = 25
        Date = 40093.449149120370000000
        Time = 40093.449149120370000000
        TabOrder = 18
      end
      object dtprk2: TDateTimePicker
        Left = 208
        Top = 3
        Width = 98
        Height = 25
        Date = 40093.449270648150000000
        Time = 40093.449270648150000000
        TabOrder = 19
      end
      object chrk: TRzCheckBox
        Left = 8
        Top = 6
        Width = 67
        Height = 19
        Caption = #20837#24211#26102#38388
        State = cbUnchecked
        TabOrder = 20
      end
      object dtpjiezhi: TDateTimePicker
        Left = 414
        Top = 65
        Width = 98
        Height = 25
        Date = 40093.449270648150000000
        Time = 40093.449270648150000000
        TabOrder = 21
      end
      object cbjiezhi: TRzCheckBox
        Left = 333
        Top = 68
        Width = 67
        Height = 19
        Caption = #25130#27490#26085#26399
        State = cbUnchecked
        TabOrder = 22
      end
      object cbtuihuo: TRzCheckBox
        Left = 668
        Top = 70
        Width = 91
        Height = 19
        Caption = #36864#36135#21608#26399#36798#21040
        State = cbUnchecked
        TabOrder = 23
      end
      object edittianshu: TRzEdit
        Left = 765
        Top = 67
        Width = 64
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 24
        OnKeyPress = edtPressCount1KeyPress
      end
    end
  end
  object ImageList1: TImageList
    Left = 816
    Top = 312
    Bitmap = {
      494C01010A0018007C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
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
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
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
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
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
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
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
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
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
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
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
      00000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300000000000000000000993300009933000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900999999000000000000000000999999009999990000000000000000000000
      000000000000000000000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000CC660000993300000000000099330000CC66000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00999999000000000099999900CCCCCC0099999900000000000000
      00000000000000000000000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000CC660000CC6600009933000099330000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC009999990099999900CCCCCC00CCCCCC00999999000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000099330000993300009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000099999900999999009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      99000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC66000099330000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCC
      CC009999990000000000000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC66000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC66000099330000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCC
      CC00CCCCCC00CCCCCC00999999000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC66000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC66000099330000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCC
      CC009999990000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000099330000993300009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000099999900999999009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      99000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      9900000000000000000000000000000000000000000000000000000000009933
      0000CC660000CC6600009933000099330000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC009999990099999900CCCCCC00CCCCCC00999999000000
      00000000000000000000000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000000000000000000009933
      0000CC660000993300000000000099330000CC66000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00999999000000000099999900CCCCCC0099999900000000000000
      00000000000000000000000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300000000000000000000993300009933000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900999999000000000000000000999999009999990000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300000000
      0000000000000000000000000000000000009933000099330000000000000000
      0000000000000000000000000000000000000000000099999900999999000000
      0000000000000000000000000000000000009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC6600009933
      00000000000000000000000000000000000099330000CC660000993300000000
      0000000000000000000000000000000000000000000099999900CCCCCC009999
      99000000000000000000000000000000000099999900CCCCCC00999999000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000099330000CC660000CC66
      00009933000000000000000000000000000099330000CC660000CC6600009933
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC009999990000000000000000000000000099999900CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000099330000CC660000CC66
      0000CC66000099330000000000000000000099330000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099999900CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E5000000000099330000CC660000CC66
      0000CC660000CC660000993300000000000099330000CC660000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B2000000000099330000CC660000CC66
      0000CC660000CC660000CC6600009933000099330000CC660000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC009999990099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC00999999000000000099330000CC660000CC66
      0000CC660000CC660000993300000000000099330000CC660000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000099330000CC660000CC66
      0000CC66000099330000000000000000000099330000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099999900CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000099330000CC660000CC66
      00009933000000000000000000000000000099330000CC660000CC6600009933
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC009999990000000000000000000000000099999900CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B2000000000099330000CC6600009933
      00000000000000000000000000000000000099330000CC660000993300000000
      0000000000000000000000000000000000000000000099999900CCCCCC009999
      99000000000000000000000000000000000099999900CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E5000000000099330000993300000000
      0000000000000000000000000000000000009933000099330000000000000000
      0000000000000000000000000000000000000000000099999900999999000000
      0000000000000000000000000000000000009999990099999900000000000000
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
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000FFFFFFFF00000000
      8003800300000000800380030000000080038003000000008003800300000000
      8003800300000000FFFFFFFF00000000BFFBBFFB00000000FFFFFFFF00000000
      BFFBBFFB00000000FFFFFFFF00000000BFFBBFFB00000000FFFFFFFF00000000
      AAABAAAB00000000FFFFFFFF00000000FDFFFDFFFFFFFFFFE0FFE8FFFFFFFFFF
      801FA05FE67FE67F001F803FE23FE23F001F001FE01FE01F000F000F800F800F
      000F000F80078007000F000F8003800300010001800180010101000180038003
      0101000180078007000F000F800F800F008F000FE01FE01F00AF002FE23FE23F
      803F803FE67FE67FE1FFE1FFFFFFFFFF8FFF8FFFFFFFFFFF07FF07FFFFFFFFFF
      83FF83FFFFFFFFFF81FF81FF9F3F9F3FC0FFC0FF8F1F8F1FE003E003870F870F
      F001F00183078307F800F80081038103F800F80080018001F800F80081038103
      F800F80083078307F800F800870F870FF800F8008F1F8F1FF800F8009F3F9F3F
      FC01FC01FFFFFFFFFE03FE03FFFFFFFF00000000000000000000000000000000
      000000000000}
  end
  object dssupplier: TDataSource
    DataSet = aqsupplier
    Left = 480
    Top = 264
  end
  object aqsupplier: TADOQuery
    Parameters = <>
    SQL.Strings = (
      
        'select ID,Name from CUST_CustomerInfo where type = 1 and custome' +
        'rstate=1')
    Left = 480
    Top = 312
  end
  object dspress: TDataSource
    DataSet = aqpress
    Left = 432
    Top = 280
  end
  object aqpress: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select ID,AbbreviatedName from BS_PressInfo')
    Left = 344
    Top = 288
  end
  object fcon: TADOConnection
    Left = 696
    Top = 280
  end
  object ds: TDataSource
    DataSet = query
    Left = 136
    Top = 264
  end
  object query: TADOQuery
    Parameters = <>
    Left = 80
    Top = 240
  end
  object PopupMenu1: TPopupMenu
    Left = 232
    Top = 320
    object N1: TMenuItem
      Caption = #20840#36873
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #24453#36890#30693
      OnClick = N2Click
    end
    object N5: TMenuItem
      Caption = '---------'
    end
    object N4: TMenuItem
      Caption = #30830#23450#36864#36135
      OnClick = N4Click
    end
    object N3: TMenuItem
      Caption = #21462#28040#29366#24577
      OnClick = N3Click
    end
  end
  object querybk: TADOQuery
    Parameters = <>
    Left = 408
    Top = 320
  end
  object stops: TADOStoredProc
    ProcedureName = 'ReturnPS'
    Parameters = <
      item
        Name = '@return'
        DataType = ftInteger
        Direction = pdReturnValue
        Value = Null
      end
      item
        Name = '@stgid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@userid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@ReturnCode'
        DataType = ftString
        Direction = pdOutput
        Size = 500
        Value = Null
      end
      item
        Name = '@Returnint'
        DataType = ftInteger
        Direction = pdOutput
        Precision = 10
        Value = Null
      end>
    Left = 592
    Top = 305
  end
  object stotk: TADOStoredProc
    ProcedureName = 'USP_BS_ReturnStorage'
    Parameters = <
      item
        Name = '@return_value'
        DataType = ftInteger
        Direction = pdReturnValue
        Value = Null
      end
      item
        Name = '@userid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@StgID'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@ReturnCode'
        DataType = ftString
        Direction = pdOutput
        Size = 500
        Value = Null
      end
      item
        Name = '@Returnint'
        DataType = ftInteger
        Direction = pdOutput
        Value = Null
      end>
    Left = 544
    Top = 305
  end
  object savedlg: TSaveDialog
    Left = 656
    Top = 280
  end
end
