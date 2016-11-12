object frmclientwanglai: Tfrmclientwanglai
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #23458#25143#20303#26469#23545#24080
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
  Position = poMainFormCenter
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
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
      BtnProperties
      BtnNextRecord
      BtnExport
      BtnPrintPreview
      BtnPrint
      BtnAlignBottom
      BtnExit)
    object BtnAlignBottom: TRzToolButton
      Left = 374
      Top = 0
      Width = 55
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 0
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
    object BtnExit: TRzToolButton
      Left = 429
      Top = 0
      Width = 55
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      GradientColorStyle = gcsSystem
      ImageIndex = 2
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
    object BtnView: TRzToolButton
      Left = 4
      Top = 0
      Width = 55
      Height = 36
      Hint = 'View'
      DisabledIndex = 5
      GradientColorStyle = gcsSystem
      ImageIndex = 4
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
    object BtnPrintPreview: TRzToolButton
      Left = 264
      Top = 0
      Width = 55
      Height = 36
      Hint = 'Print Preview'
      DisabledIndex = 7
      GradientColorStyle = gcsSystem
      ImageIndex = 6
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #39044#35272#13'[F7]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnPrintPreviewClick
    end
    object BtnPrint: TRzToolButton
      Left = 319
      Top = 0
      Width = 55
      Height = 36
      Hint = 'Print'
      DisabledIndex = 9
      GradientColorStyle = gcsSystem
      ImageIndex = 8
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #25171#21360#13'[F8]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnPrintClick
    end
    object BtnProperties: TRzToolButton
      Left = 59
      Top = 0
      Width = 75
      Height = 36
      Hint = 'Properties'
      DisabledIndex = 11
      GradientColorStyle = gcsSystem
      DropDownMenu = pmdz
      ImageIndex = 10
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      ToolStyle = tsDropDown
      VisualStyle = vsGradient
      Caption = #23545#36134'[F3]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = BtnPropertiesClick
    end
    object BtnNextRecord: TRzToolButton
      Left = 134
      Top = 0
      Width = 75
      Height = 36
      Hint = 'Next Record'
      DisabledIndex = 13
      GradientColorStyle = gcsSystem
      DropDownMenu = pmfapiao
      ImageIndex = 12
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      ToolStyle = tsDropDown
      VisualStyle = vsGradient
      Caption = #24320#25454#21457#31080'[F4]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object BtnExport: TRzToolButton
      Left = 209
      Top = 0
      Width = 55
      Height = 36
      Hint = 'Export'
      DisabledIndex = 15
      GradientColorStyle = gcsSystem
      ImageIndex = 14
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
  end
  object Panel1: TPanel
    Left = 0
    Top = 36
    Width = 1012
    Height = 676
    Align = alClient
    BevelOuter = bvNone
    Caption = 'Panel1'
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 584
      Top = 0
      Width = 428
      Height = 144
      Align = alRight
      Caption = #23458#25143#20449#24687
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      object Label7: TLabel
        Left = 245
        Top = 73
        Width = 24
        Height = 17
        Caption = #20256#30495
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 16
        Top = 73
        Width = 36
        Height = 17
        Caption = #30005'   '#35805
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 16
        Top = 102
        Width = 36
        Height = 17
        Caption = #22320'   '#22336
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 16
        Top = 44
        Width = 36
        Height = 17
        Caption = #32852#31995#20154
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 245
        Top = 44
        Width = 24
        Height = 17
        Caption = #24080#21495
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
        Width = 36
        Height = 17
        Caption = #24050'   '#32467
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 153
        Top = 15
        Width = 24
        Height = 17
        Caption = #26410#32467
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object Label10: TLabel
        Left = 285
        Top = 15
        Width = 48
        Height = 17
        Caption = #36134#25143#20313#39069
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
      end
      object editfax: TEdit
        Left = 273
        Top = 71
        Width = 147
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 1
      end
      object edittel: TEdit
        Left = 56
        Top = 71
        Width = 134
        Height = 23
        Ctl3D = False
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 3
      end
      object editaddress: TEdit
        Left = 56
        Top = 100
        Width = 364
        Height = 23
        Ctl3D = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 7
      end
      object editcontact: TEdit
        Left = 56
        Top = 42
        Width = 134
        Height = 23
        Ctl3D = False
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 5
      end
      object editzhanhao: TEdit
        Left = 273
        Top = 42
        Width = 147
        Height = 23
        Ctl3D = False
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 0
      end
      object edityijie: TEdit
        Left = 56
        Top = 13
        Width = 84
        Height = 23
        Ctl3D = False
        ImeName = #20013#25991' ('#31616#20307') - '#26497#28857#20116#31508
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 2
      end
      object editweijie: TEdit
        Left = 182
        Top = 13
        Width = 84
        Height = 23
        Ctl3D = False
        ImeName = #20013#25991' ('#31616#20307') - '#26497#28857#20116#31508
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 4
      end
      object edityue: TEdit
        Left = 336
        Top = 13
        Width = 84
        Height = 23
        Ctl3D = False
        ImeName = #20013#25991' ('#31616#20307') - '#26497#28857#20116#31508
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 6
      end
    end
    object GroupBox5: TGroupBox
      Left = 0
      Top = 0
      Width = 572
      Height = 144
      Align = alLeft
      Caption = #26597#35810#26465#20214
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      object Label15: TLabel
        Left = 336
        Top = 73
        Width = 18
        Height = 17
        Caption = '>='
      end
      object Label16: TLabel
        Left = 452
        Top = 73
        Width = 18
        Height = 17
        Caption = '<='
      end
      object chclient: TCheckBox
        Left = 16
        Top = 16
        Width = 78
        Height = 17
        Caption = #23458#25143#21517#31216
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
      object editjianshuo: TEdit
        Left = 99
        Top = 12
        Width = 54
        Height = 25
        AutoSize = False
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 0
        OnKeyPress = editjianshuoKeyPress
      end
      object cbdanwei: TComboBox
        Left = 152
        Top = 12
        Width = 410
        Height = 25
        BevelKind = bkFlat
        Ctl3D = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 17
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 2
        OnChange = cbdanweiChange
        OnSelect = cbdanweiSelect
      end
      object dtpend: TDateTimePicker
        Left = 282
        Top = 99
        Width = 95
        Height = 25
        Date = 40253.725135162040000000
        Time = 40253.725135162040000000
        TabOrder = 3
      end
      object dtpbegin: TDateTimePicker
        Left = 99
        Top = 99
        Width = 93
        Height = 25
        Date = 40253.724745266210000000
        Time = 40253.724745266210000000
        TabOrder = 4
      end
      object chstart: TCheckBox
        Left = 16
        Top = 102
        Width = 68
        Height = 17
        Caption = #36215#22987#26102#38388
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 5
      end
      object chend: TCheckBox
        Left = 207
        Top = 102
        Width = 68
        Height = 17
        Caption = #32467#26463#26102#38388
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 6
      end
      object chstate: TCheckBox
        Left = 16
        Top = 45
        Width = 69
        Height = 17
        Caption = #23545#36134#29366#24577
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 7
      end
      object chfapiao: TCheckBox
        Left = 391
        Top = 45
        Width = 50
        Height = 17
        Caption = #21457#31080
        TabOrder = 8
      end
      object cbstate: TComboBox
        Left = 99
        Top = 41
        Width = 93
        Height = 25
        BevelKind = bkFlat
        Style = csDropDownList
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
        TabOrder = 9
        Text = #26410#23545#36134
        Items.Strings = (
          #26410#23545#36134
          #24050#23545#36134)
      end
      object cbfapiao: TComboBox
        Left = 447
        Top = 41
        Width = 115
        Height = 25
        BevelKind = bkFlat
        Style = csDropDownList
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
        TabOrder = 10
        Text = #26410#24320#21457#31080
        Items.Strings = (
          #26410#24320#21457#31080
          #24050#24320#21457#31080)
      end
      object ch1: TCheckBox
        Left = 16
        Top = 74
        Width = 69
        Height = 17
        Caption = #21457#36135
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 11
      end
      object ch3: TCheckBox
        Left = 207
        Top = 74
        Width = 58
        Height = 17
        Caption = #36864'    '#36135
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 12
      end
      object ch2: TCheckBox
        Left = 116
        Top = 74
        Width = 69
        Height = 17
        Caption = #26679#20070#22788#29702
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 13
      end
      object chjiekuan: TCheckBox
        Left = 207
        Top = 45
        Width = 69
        Height = 17
        Caption = #32467#27454#29366#24577
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 14
      end
      object cbjiekuanstate: TComboBox
        Left = 282
        Top = 41
        Width = 95
        Height = 25
        BevelKind = bkFlat
        Style = csDropDownList
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
        TabOrder = 15
        Text = #26410#32467#27454
        Items.Strings = (
          #26410#32467#27454
          #24050#32467#37096#20998
          #26410#23457#26680
          #24050#32467#27454)
      end
      object chfapiaohao: TCheckBox
        Left = 391
        Top = 102
        Width = 58
        Height = 17
        Caption = #21457#31080#21495
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 16
      end
      object edfapiaohao: TEdit
        Left = 447
        Top = 99
        Width = 115
        Height = 25
        AutoSize = False
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 17
      end
      object chshiyang: TCheckBox
        Left = 282
        Top = 74
        Width = 51
        Height = 17
        Caption = #23454#27915
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentFont = False
        TabOrder = 18
      end
      object edmin: TEdit
        Left = 361
        Top = 71
        Width = 81
        Height = 23
        Ctl3D = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 19
      end
      object edmax: TEdit
        Left = 479
        Top = 71
        Width = 83
        Height = 23
        Ctl3D = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 20
      end
    end
    object dg1: TDBGrid
      Left = 0
      Top = 202
      Width = 1012
      Height = 546
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ParentFont = False
      PopupMenu = pm
      TabOrder = 2
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      OnDblClick = dg1DblClick
      OnEnter = dg1Enter
      OnTitleClick = dg1TitleClick
      Columns = <
        item
          Expanded = False
          FieldName = 'ID'
          ReadOnly = True
          Visible = False
        end
        item
          Expanded = False
          FieldName = #24207#21495
          ReadOnly = True
          Width = 30
          Visible = True
        end
        item
          Expanded = False
          FieldName = #23458#25143#21517#31216
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = #21333#21495
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = #26085#26399
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = #25968#37327
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 45
          Visible = True
        end
        item
          Expanded = False
          FieldName = #30721#27915
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = #23454#27915
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = #23545#26041#36134#21153
          Title.Alignment = taCenter
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = #32418#20914
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = #24050#32467
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = #26410#32467
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = #23545#36134#29366#24577
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = #21457#31080
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 35
          Visible = True
        end
        item
          Expanded = False
          FieldName = #32467#27454#29366#24577
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = #38468#21152#36153#29992
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'totalyingfu'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #24635#24212#25910
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = #32467#27454#21333#21495
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'fapiaotext'
          Title.Alignment = taCenter
          Title.Caption = #21457#31080#21495
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = #22791#27880
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 120
          Visible = True
        end>
    end
    object dg: TDBGridEh
      Left = 0
      Top = 144
      Width = 1012
      Height = 532
      Align = alBottom
      DataSource = DataSource2
      Flat = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      FooterColor = clWindow
      FooterFont.Charset = ANSI_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -12
      FooterFont.Name = #24494#36719#38597#40657
      FooterFont.Style = []
      FooterRowCount = 1
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ParentFont = False
      PopupMenu = pm
      SumList.Active = True
      TabOrder = 3
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -12
      TitleFont.Name = #24494#36719#38597#40657
      TitleFont.Style = []
      Columns = <
        item
          EditButtons = <>
          FieldName = 'ID'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = 'id'
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Visible = False
        end
        item
          EditButtons = <>
          FieldName = #24207#21495
          Footer.Alignment = taCenter
          Footer.Value = #21512#35745
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 40
        end
        item
          EditButtons = <>
          FieldName = #23458#25143#21517#31216
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 150
        end
        item
          EditButtons = <>
          FieldName = #21333#21495
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
        end
        item
          EditButtons = <>
          FieldName = #26085#26399
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
        end
        item
          EditButtons = <>
          FieldName = #25968#37327
          Footer.Alignment = taCenter
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 45
        end
        item
          EditButtons = <>
          FieldName = #30721#27915
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
        end
        item
          EditButtons = <>
          FieldName = #23454#27915
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
        end
        item
          EditButtons = <>
          FieldName = #23545#26041#36134#21153
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 70
        end
        item
          EditButtons = <>
          FieldName = #32418#20914
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
        end
        item
          EditButtons = <>
          FieldName = #24050#32467
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
        end
        item
          EditButtons = <>
          FieldName = #26410#32467
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
        end
        item
          EditButtons = <>
          FieldName = #23545#36134#29366#24577
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
        end
        item
          EditButtons = <>
          FieldName = #21457#31080
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 35
        end
        item
          EditButtons = <>
          FieldName = #32467#27454#29366#24577
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = #38468#21152#36153#29992
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 65
        end
        item
          EditButtons = <>
          FieldName = 'totalyingfu'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #24635#24212#20184
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
        end
        item
          EditButtons = <>
          FieldName = #32467#27454#21333#21495
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 100
        end
        item
          EditButtons = <>
          FieldName = 'fapiaotext'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21457#31080#21495
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = #22791#27880
          Footers = <>
          Title.Alignment = taCenter
          Title.Font.Charset = ANSI_CHARSET
          Title.Font.Color = clWindowText
          Title.Font.Height = -14
          Title.Font.Name = #24494#36719#38597#40657
          Title.Font.Style = []
          Width = 120
        end>
    end
  end
  object duizhang: TRvProject
    Engine = RvSystem1
    Left = 704
    Top = 256
  end
  object query: TADOQuery
    CursorType = ctStatic
    AfterPost = queryAfterPost
    Parameters = <>
    SQL.Strings = (
      '')
    Left = 672
    Top = 440
  end
  object aqprint: TADOQuery
    ConnectionString = 
      'Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security In' +
      'fo=False;Initial Catalog=kong;Data Source=PEIDETHREE'
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      
        ' select  A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(1' +
        '0)) as '#39'xuhao'#39',B.Name as '#39'name'#39',StgNtCodeStr as '#39'danhao'#39',CONVERT' +
        '(varchar(12),Hdtime,111) as  '#39'rkqi'#39', TotalAmount as '#39'totalamount' +
        #39',TotalFixedPrice as '#39'mayang'#39',TotalDiscountedPrice as '#39'siyang'#39',c' +
        'hecked  as '#39'yijie'#39',nochecked as '#39'weijie'#39',  remarks as '#39'bk'#39',case ' +
        'A.cwstate when 0 then '#39#26410#23545#36134#39' when 1 then '#39#24050#23545#36134#39' else '#39'yijie'#27454#39' end ' +
        ' as '#39'cwstate'#39',case A.fapiao when 0 then '#39#26410#24320#21457#31080#39' else '#39#24050#24320#21457#31080#39' end a' +
        's '#39'fapiao'#39' from BS_StorageNoteHeader  A left join CUST_CustomerI' +
        'nfo B on A.supplierid = B.id  where A.stgid = 0 union   select 9' +
        '99999999,null,'#39#21512#35745#39',NULL,NULL,sum(TotalAmount) as TotalAmount,sum' +
        '(TotalFixedPrice) as TotalFixedPrice,sum(TotalDiscountedPrice) a' +
        's DiscountedPrice,sum(checked) as checked,sum(nochecked) as  noc' +
        'hecked,NULL,NULL,NULL from BS_StorageNoteHeader A  where A.stgid' +
        ' = 0 order by id asc ')
    Left = 536
    Top = 416
  end
  object Rvcondizhang: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqprint
    Left = 456
    Top = 376
  end
  object DataSource2: TDataSource
    DataSet = query
    Left = 456
    Top = 288
  end
  object RvSystem1: TRvSystem
    TitleSetup = 'Output Options'
    TitleStatus = 'Report Status'
    TitlePreview = 'Report Preview'
    SystemFiler.StatusFormat = #27491#22312#25171#21360#31532'%p'#39029'...'
    SystemPreview.FormState = wsMaximized
    SystemPreview.ZoomFactor = 100.000000000000000000
    SystemPrinter.ScaleX = 100.000000000000000000
    SystemPrinter.ScaleY = 100.000000000000000000
    SystemPrinter.StatusFormat = 'Printing page %p'
    SystemPrinter.Title = 'Rave Report'
    SystemPrinter.UnitsFactor = 1.000000000000000000
    Left = 688
    Top = 336
  end
  object savedlg: TSaveDialog
    Filter = 'CSV'#25991#20214'(*.CSV)|*.CSV'
    Left = 624
    Top = 208
  end
  object fcon: TADOConnection
    Left = 520
    Top = 208
  end
  object pmdz: TPopupMenu
    Left = 120
    Top = 256
    object N4: TMenuItem
      Caption = #23545#36134
      Checked = True
      OnClick = N4Click
    end
    object N5: TMenuItem
      AutoCheck = True
      Caption = #21462#28040#23545#36134
      OnClick = N5Click
    end
  end
  object pmfapiao: TPopupMenu
    Left = 192
    Top = 208
    object N2: TMenuItem
      AutoCheck = True
      Caption = #24320#25454#21457#31080
      Checked = True
    end
    object N3: TMenuItem
      AutoCheck = True
      Caption = #21462#28040#24320#25454#21457#31080
    end
  end
  object pm: TPopupMenu
    Left = 240
    Top = 256
    object N1: TMenuItem
      Caption = #20840#36873
    end
  end
end
