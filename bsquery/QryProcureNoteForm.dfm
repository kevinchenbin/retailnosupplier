inherited frmQryProcureNote: TfrmQryProcureNote
  Caption = #37319#36141#26597#35810
  ClientHeight = 712
  ClientWidth = 1012
  OnKeyDown = FormKeyDown
  ExplicitWidth = 1028
  ExplicitHeight = 750
  PixelsPerInch = 96
  TextHeight = 13
  object pgcntrlResult: TRzPageControl [0]
    Left = 0
    Top = 177
    Width = 1012
    Height = 535
    ActivePage = tbshtByNtHeader
    Align = alClient
    DragIndicatorColor = 5263440
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    FlatColor = clMoneyGreen
    ParentFont = False
    TabIndex = 0
    TabOrder = 2
    TabStyle = tsBackSlant
    FixedDimension = 23
    object tbshtByNtHeader: TRzTabSheet
      Tag = 1
      Caption = #25353#21333
      object dbgrdByNtHeader: TDBGridEh
        Left = 0
        Top = 0
        Width = 1008
        Height = 508
        Align = alClient
        DataSource = dsrcByNtHeader
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = ANSI_CHARSET
        FooterFont.Color = clNavy
        FooterFont.Height = -12
        FooterFont.Name = #24494#36719#38597#40657
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        ReadOnly = True
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -12
        TitleFont.Name = #24494#36719#38597#40657
        TitleFont.Style = []
        OnDblClick = dbgrdByNtHeaderDblClick
        OnTitleClick = dbgrdByNtHeaderTitleClick
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #21333#21495
            Width = 100
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26085#26399
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'ProcureNoteHeadeRemarks'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #22791#27880
            Width = 150
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Width = 120
          end
          item
            EditButtons = <>
            FieldName = 'Operatorname'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25805#20316#21592
            Width = 50
          end>
      end
    end
    object tbshtByNote: TRzTabSheet
      Tag = 2
      Caption = #26126#32454
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object dbgrdByNote: TDBGridEh
        Left = 0
        Top = 0
        Width = 1008
        Height = 508
        Align = alClient
        DataSource = dsrcByNote
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = ANSI_CHARSET
        FooterFont.Color = clNavy
        FooterFont.Height = -12
        FooterFont.Name = #24494#36719#38597#40657
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        PopupMenu = PopupMenu1
        ReadOnly = True
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -12
        TitleFont.Name = #24494#36719#38597#40657
        TitleFont.Style = []
        OnTitleClick = dbgrdByNoteTitleClick
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footer.FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830
            Width = 120
          end
          item
            EditButtons = <>
            FieldName = 'ISBN'
            Footers = <>
            Title.Alignment = taCenter
            Width = 100
          end
          item
            EditButtons = <>
            FieldName = 'BookName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20070#21517
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'UserDefCode'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #33258#32534#30721
            Width = 75
          end
          item
            EditButtons = <>
            FieldName = 'Price'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23450#20215
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'Author'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20316#32773
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #29256#21035
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #21333#21495
            Width = 100
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26085#26399
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'Discount'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25240#25187
            Width = 45
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'ordercode'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25910#35746#21333#21495
            Visible = False
            Width = 71
          end
          item
            EditButtons = <>
            FieldName = 'clientname'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #27969#21521
            Visible = False
            Width = 78
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Width = 35
          end
          item
            EditButtons = <>
            FieldName = 'PressDate'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20986#29256#26085#26399
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #31867#21035
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Width = 120
          end
          item
            EditButtons = <>
            FieldName = 'bookcatalogid'
            Footers = <>
            Visible = False
          end>
      end
    end
    object tbshtByCustomer: TRzTabSheet
      Tag = 3
      Caption = #20379#24212#21830
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object dbgrdByCustomer: TDBGridEh
        Left = 0
        Top = 0
        Width = 1008
        Height = 508
        Align = alClient
        DataSource = dsrcByCustomer
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = ANSI_CHARSET
        FooterFont.Color = clNavy
        FooterFont.Height = -12
        FooterFont.Name = #24494#36719#38597#40657
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        ReadOnly = True
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = ANSI_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -12
        TitleFont.Name = #24494#36719#38597#40657
        TitleFont.Style = []
        OnTitleClick = dbgrdByCustomerTitleClick
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Width = 180
          end>
      end
    end
    object tbshtByBktype: TRzTabSheet
      Tag = 4
      Caption = #31867#21035
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object dbgrdByBktype: TDBGridEh
        Left = 0
        Top = 0
        Width = 1008
        Height = 508
        Align = alClient
        DataSource = dsrcByBktype
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = ANSI_CHARSET
        FooterFont.Color = clNavy
        FooterFont.Height = -12
        FooterFont.Name = #24494#36719#38597#40657
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        ReadOnly = True
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnTitleClick = dbgrdByBktypeTitleClick
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #31867#21035
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 180
          end>
      end
    end
    object tbshtByPress: TRzTabSheet
      Tag = 5
      Caption = #29256#21035
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object dbgrdByPress: TDBGridEh
        Left = 0
        Top = 0
        Width = 1008
        Height = 508
        Align = alClient
        DataSource = dsrcByPress
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #24494#36719#38597#40657
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = ANSI_CHARSET
        FooterFont.Color = clNavy
        FooterFont.Height = -12
        FooterFont.Name = #24494#36719#38597#40657
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        ReadOnly = True
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnTitleClick = dbgrdByPressTitleClick
        Columns = <
          item
            Alignment = taCenter
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #29256#21035
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 200
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'RecAmount'
            Footer.FieldName = 'RecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24050#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'UnrecAmount'
            Footer.FieldName = 'UnrecAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26410#21040
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21517
            Title.Font.Charset = ANSI_CHARSET
            Title.Font.Color = clNavy
            Title.Font.Height = -12
            Title.Font.Name = #24494#36719#38597#40657
            Title.Font.Style = []
            Width = 180
          end>
      end
    end
  end
  object rztlbr1: TRzToolbar [1]
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
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      tlbtnQry
      tlbtnExport
      BtnAlignBottom
      tlbtnExit)
    object tlbtnQry: TRzToolButton
      Left = 4
      Top = 0
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26597#35810#13'(&F)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = tlbtnQryClick
    end
    object tlbtnExport: TRzToolButton
      Left = 64
      Top = 0
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20986#13'[F6]'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      OnClick = tlbtnExportClick
    end
    object tlbtnExit: TRzToolButton
      Left = 184
      Top = 0
      Width = 60
      Height = 36
      GradientColorStyle = gcsSystem
      ImageIndex = 4
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
      OnClick = tlbtnExitClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 124
      Top = 0
      Width = 60
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
  object grpbx1: TRzGroupBox [2]
    Left = 0
    Top = 36
    Width = 1012
    Height = 141
    Align = alTop
    BorderColor = clMoneyGreen
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentColor = True
    ParentFont = False
    TabOrder = 1
    VisualStyle = vsClassic
    object lbl1: TLabel
      Left = 458
      Top = 51
      Width = 18
      Height = 17
      Caption = '>='
    end
    object lbl2: TLabel
      Left = 537
      Top = 51
      Width = 18
      Height = 17
      Caption = '<='
    end
    object lbl3: TLabel
      Left = 458
      Top = 81
      Width = 18
      Height = 17
      Caption = '>='
    end
    object lbl4: TLabel
      Left = 537
      Top = 81
      Width = 18
      Height = 17
      Caption = '<='
    end
    object Label36: TLabel
      Left = 458
      Top = 21
      Width = 18
      Height = 17
      Caption = '>='
    end
    object Label37: TLabel
      Left = 537
      Top = 21
      Width = 18
      Height = 17
      Caption = '<='
    end
    object SpeedButton1: TSpeedButton
      Left = 810
      Top = 49
      Width = 27
      Height = 23
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
      OnClick = SpeedButton1Click
    end
    object chckbxStartTime: TRzCheckBox
      Left = 16
      Top = 20
      Width = 67
      Height = 19
      Caption = #36215#22987#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 0
    end
    object chckbxEndTime: TRzCheckBox
      Left = 16
      Top = 51
      Width = 67
      Height = 19
      Caption = #32467#26463#26102#38388
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 1
    end
    object chckbxBookName: TRzCheckBox
      Left = 223
      Top = 20
      Width = 43
      Height = 19
      Caption = #20070#21517
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 2
    end
    object chckbxISBN: TRzCheckBox
      Left = 223
      Top = 50
      Width = 43
      Height = 19
      Caption = #20070#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 3
    end
    object chckbxCustomer: TRzCheckBox
      Left = 16
      Top = 111
      Width = 55
      Height = 19
      Caption = #20379#24212#21830
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 4
    end
    object chckbxUserDefNum: TRzCheckBox
      Left = 16
      Top = 80
      Width = 55
      Height = 19
      Caption = #33258#32534#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 5
    end
    object chckbxPrice: TRzCheckBox
      Left = 411
      Top = 80
      Width = 43
      Height = 19
      Caption = #23450#20215
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 6
    end
    object chckbxAuthor: TRzCheckBox
      Left = 223
      Top = 80
      Width = 43
      Height = 19
      Caption = #20316#32773
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 7
    end
    object chckbxAmount: TRzCheckBox
      Left = 411
      Top = 50
      Width = 43
      Height = 19
      Caption = #25968#37327
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 8
    end
    object chckbxPress: TRzCheckBox
      Left = 630
      Top = 20
      Width = 43
      Height = 19
      Caption = #29256#21035
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 9
    end
    object chckbxType: TRzCheckBox
      Left = 630
      Top = 50
      Width = 43
      Height = 19
      Caption = #31867#21035
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 10
    end
    object chckbxRemarks: TRzCheckBox
      Left = 630
      Top = 111
      Width = 43
      Height = 19
      Caption = #22791#27880
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 11
    end
    object chckbxStorage: TRzCheckBox
      Left = 630
      Top = 80
      Width = 43
      Height = 19
      Caption = #24215#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 12
    end
    object edtBookName: TRzEdit
      Left = 270
      Top = 19
      Width = 121
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 13
      OnChange = edtBookNameChange
    end
    object edtISBN: TRzEdit
      Left = 270
      Top = 49
      Width = 121
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MaxLength = 20
      ParentCtl3D = False
      TabOrder = 14
      OnChange = edtISBNChange
    end
    object edtUserDefNum: TRzEdit
      Left = 87
      Top = 78
      Width = 121
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 15
      OnChange = edtUserDefNumChange
    end
    object edtAuthor: TRzEdit
      Left = 270
      Top = 78
      Width = 121
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 16
      OnChange = edtAuthorChange
    end
    object edtPress: TRzEdit
      Tag = 1
      Left = 676
      Top = 19
      Width = 37
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 17
      OnKeyPress = edtPressKeyPress
    end
    object edtRemarks: TRzEdit
      Left = 676
      Top = 108
      Width = 316
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 18
      OnChange = edtRemarksChange
    end
    object edtCustomer: TRzEdit
      Tag = 2
      Left = 87
      Top = 108
      Width = 37
      Height = 23
      AutoSize = False
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 19
      OnKeyPress = edtPressKeyPress
    end
    object numedtMinPrice: TRzNumericEdit
      Left = 478
      Top = 78
      Width = 55
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 20
      OnChange = numedtMinPriceChange
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0.00'
    end
    object numedtMinAmount: TRzNumericEdit
      Left = 478
      Top = 49
      Width = 55
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 21
      OnChange = numedtMinAmountChange
      AllowBlank = True
      DisplayFormat = '###,##0;-###,##0'
    end
    object numedtMaxPrice: TRzNumericEdit
      Left = 558
      Top = 78
      Width = 55
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 22
      OnChange = numedtMaxPriceChange
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0.00'
    end
    object numedtMaxAmount: TRzNumericEdit
      Left = 558
      Top = 49
      Width = 55
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 23
      OnChange = numedtMaxAmountChange
      AllowBlank = True
      DisplayFormat = '###,##0;-###,##0'
    end
    object dblkpcbbPress: TRzDBLookupComboBox
      Left = 712
      Top = 19
      Width = 95
      Height = 23
      Ctl3D = False
      DataField = 'PressID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'AbbreviatedName'
      ListSource = dsrcPress
      ParentCtl3D = False
      TabOrder = 24
      OnClick = dblkpcbbPressClick
    end
    object dblkpcbbCustomer: TRzDBLookupComboBox
      Left = 123
      Top = 108
      Width = 268
      Height = 23
      Ctl3D = False
      DataField = 'CustomerID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcCustomer
      ParentCtl3D = False
      TabOrder = 25
      OnClick = dblkpcbbCustomerClick
    end
    object dblkpcbbStorage: TRzDBLookupComboBox
      Left = 676
      Top = 78
      Width = 131
      Height = 23
      Ctl3D = False
      DataField = 'StorageID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcStorage
      ParentCtl3D = False
      TabOrder = 26
      OnClick = dblkpcbbStorageClick
    end
    object chdiscount: TCheckBox
      Left = 411
      Top = 22
      Width = 43
      Height = 17
      Caption = #25240#25187
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 27
    end
    object edmaxdiscount: TEdit
      Left = 558
      Top = 19
      Width = 55
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 28
      OnChange = edmaxdiscountChange
    end
    object chstaff: TCheckBox
      Left = 411
      Top = 111
      Width = 55
      Height = 17
      Caption = #25805#20316#21592
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 29
    end
    object chnocheck: TCheckBox
      Left = 842
      Top = 80
      Width = 55
      Height = 17
      Caption = #26410#21040#36807
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 30
    end
    object chcheckpart: TCheckBox
      Left = 842
      Top = 51
      Width = 67
      Height = 17
      Caption = #24050#21040#37096#20998
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 31
    end
    object chchecked: TCheckBox
      Left = 924
      Top = 51
      Width = 68
      Height = 17
      Caption = #24050#21040#20840#37096
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 32
    end
    object edmindiscount: TEdit
      Left = 478
      Top = 19
      Width = 55
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 33
      OnChange = edmindiscountChange
    end
    object dtedtStart: TRzDateTimePicker
      Left = 87
      Top = 18
      Width = 121
      Height = 25
      Date = 40746.458519027780000000
      Time = 40746.458519027780000000
      TabOrder = 34
    end
    object dtedtEnd: TRzDateTimePicker
      Left = 87
      Top = 48
      Width = 121
      Height = 25
      Date = 40746.458607939810000000
      Time = 40746.458607939810000000
      TabOrder = 35
    end
    object chdanhao: TRzCheckBox
      Left = 842
      Top = 20
      Width = 43
      Height = 19
      Caption = #21333#21495
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      State = cbUnchecked
      TabOrder = 36
    end
    object eddanhao: TRzEdit
      Left = 887
      Top = 19
      Width = 105
      Height = 23
      Ctl3D = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentCtl3D = False
      TabOrder = 37
      OnChange = eddanhaoChange
    end
    object dblkpcbbstaff: TRzDBLookupComboBox
      Left = 478
      Top = 108
      Width = 135
      Height = 23
      Ctl3D = False
      DataField = 'StaffID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcstaff
      ParentCtl3D = False
      TabOrder = 38
    end
    object edtyname: TEdit
      Left = 712
      Top = 49
      Width = 95
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 39
    end
    object edpyquery: TEdit
      Left = 676
      Top = 49
      Width = 37
      Height = 23
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 40
      OnKeyPress = edpyqueryKeyPress
    end
  end
  inherited qryUserAuthority: TADOQuery
    Left = 512
    Top = 496
  end
  inherited aquerybs: TADOQuery
    Left = 464
    Top = 368
  end
  object dsetByNtHeader: TADODataSet
    Parameters = <>
    Left = 248
    Top = 280
  end
  object dsrcByNtHeader: TDataSource
    DataSet = dsetByNtHeader
    Left = 48
    Top = 280
  end
  object dsetByNote: TADODataSet
    Parameters = <>
    Left = 304
    Top = 328
  end
  object dsrcByNote: TDataSource
    DataSet = dsetByNote
    Left = 120
    Top = 272
  end
  object dsetByCustomer: TADODataSet
    Parameters = <>
    Left = 264
    Top = 352
  end
  object dsrcByCustomer: TDataSource
    DataSet = dsetByCustomer
    Left = 160
    Top = 384
  end
  object dsetByBktype: TADODataSet
    Parameters = <>
    Left = 512
    Top = 296
  end
  object dsrcByBktype: TDataSource
    DataSet = dsetByBktype
    Left = 24
    Top = 328
  end
  object dsetByPress: TADODataSet
    Parameters = <>
    Left = 448
    Top = 304
  end
  object dsrcByPress: TDataSource
    DataSet = dsetByPress
    Left = 304
    Top = 424
  end
  object spQryNote: TADOStoredProc
    CacheSize = 1000
    LockType = ltBatchOptimistic
    ProcedureName = 'USP_QRY_Get_NoteInfo;1'
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@Start'
        Attributes = [paNullable]
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@End'
        Attributes = [paNullable]
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@Name'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 100
        Value = Null
      end
      item
        Name = '@UserDefCode'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 10
        Value = Null
      end
      item
        Name = '@PressID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@ISBN'
        Attributes = [paNullable]
        DataType = ftString
        Size = 15
        Value = Null
      end
      item
        Name = '@MaxPrice'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@MinPrice'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@BktypeID'
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
        Name = '@Author'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 10
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
        Name = '@BkstackID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@MaxAmount'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@MinAmount'
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
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@SearchMode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@NoteCode'
        DataType = ftString
        Size = 20
        Value = Null
      end
      item
        Name = '@type'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@return'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@lost'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@damage'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@staff'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@mindiscount'
        Attributes = [paNullable]
        DataType = ftFloat
        Value = Null
      end
      item
        Name = '@maxdiscount'
        Attributes = [paNullable]
        DataType = ftFloat
        Value = Null
      end
      item
        Name = '@check'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@nocheck'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@checkpart'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@checked'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end>
    Left = 368
    Top = 472
  end
  object dsetCustomer: TADODataSet
    CursorType = ctStatic
    CommandText = 
      'select ID, Name from CUST_CustomerInfo where Type=1 and customer' +
      'state=1 order by name'
    Parameters = <>
    Left = 360
    Top = 336
  end
  object dsrcCustomer: TDataSource
    DataSet = dsetCustomer
    Left = 88
    Top = 376
  end
  object dsrcPress: TDataSource
    DataSet = dsetPress
    Left = 168
    Top = 328
  end
  object dsetBookType: TADODataSet
    CursorType = ctStatic
    CommandText = 'select ID, Name from BS_BookType where ParentID=1'
    Parameters = <>
    Left = 520
    Top = 424
  end
  object dsrcBookType: TDataSource
    DataSet = dsetBookType
    Left = 608
    Top = 424
  end
  object dsrcStorage: TDataSource
    DataSet = dsetStorage
    Left = 16
    Top = 368
  end
  object dsetStorage: TADODataSet
    CursorType = ctStatic
    CommandText = 'select ID, Name from SYS_StorageInfo'
    Parameters = <>
    Left = 160
    Top = 464
  end
  object dsrcBookstack: TDataSource
    DataSet = dsetBookstack
    Left = 168
    Top = 256
  end
  object dsetBookstack: TADODataSet
    CursorType = ctStatic
    CommandText = 'select ID, Name from STK_BookstackInfo where StgID=0'
    Parameters = <>
    Left = 80
    Top = 456
  end
  object qryItems: TADOQuery
    Parameters = <>
    Left = 640
    Top = 368
  end
  object ImageList1: TImageList
    Left = 432
    Top = 416
    Bitmap = {
      494C010108000A00BC0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900999999000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      99009999990099999900999999000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      99009999990099999900999999000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      99000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      00000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC000000000000000000000000000000000000000000CCCC
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
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      990000000000000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E500CC996600CC996600CC996600CC99
      6600CC996600CC996600CC99660000000000000000003399CC00006699000066
      9900006699000066990000669900006699009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B200CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B200CC996600FFFFFF00FFFFFF00CC99
      6600CC996600CC996600CC99660000000000000000003399CC0099FFFF0099FF
      FF003399CC003399CC003399CC003399CC009999990000000000000000009999
      9900999999009999990099999900000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E500CC996600FFFFFF00FFFFFF00CC99
      6600E5E5E500CC9966000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC00CCFFFF0000669900000000009999990000000000000000009999
      9900E5E5E5009999990000000000000000000000000099999900CCCCCC00CCCC
      CC0099999900CCCCCC0099999900000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E50000000000CC996600FFFFFF00FFFFFF00CC99
      6600CC996600000000000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC000066990000000000000000009999990000000000000000009999
      9900999999000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E5000000000000000000CC996600CC996600CC996600CC99
      660000000000000000000000000000000000000000003399CC003399CC003399
      CC003399CC000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      990099999900000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FDFFFDFFFFFFFFFFE0FFE8FFFFFFFFFF
      801FA05F80038003001F803F80038003001F001F80038003000F000F80038003
      000F000F80038003000F000FFFFFFFFF00010001BFFBBFFB01010001FFFFFFFF
      01010001BFFBBFFB000F000FFFFFFFFF008F000FBFFBBFFB00AF002FFFFFFFFF
      803F803FAAABAAABE1FFE1FFFFFFFFFF8FFF8FFFFFFFFFFF07FF07FFFFDFFFDF
      83FF83FFFFCFFFCF81FF81FFE007E007C0FFC0FFFFCFFFCFE003E003FFDFFFDF
      F001F001FFFFFFFFF800F80001800180F800F80001807D80F800F80001807D80
      F800F80001807D80F800F80001807D80F800F80001806180F800F80003816381
      FC01FC0107836783FE03FE030F870F8700000000000000000000000000000000
      000000000000}
  end
  object dsetPress: TADODataSet
    CommandText = 'select ID,PresentNum, AbbreviatedName from BS_PressInfo'
    Parameters = <>
    Left = 288
    Top = 384
  end
  object savedlg: TSaveDialog
    Left = 720
    Top = 264
  end
  object dsrcstaff: TDataSource
    DataSet = dsetstaff
    Left = 816
    Top = 280
  end
  object dsetstaff: TADODataSet
    CommandText = 
      'select cast(stgid as nvarchar(3)) + '#39#24215#39' + name as name,stgid,id ' +
      'from sys_user'
    Parameters = <>
    Left = 888
    Top = 288
  end
  object PopupMenu1: TPopupMenu
    Left = 400
    Top = 360
    object N1: TMenuItem
      Caption = #21382#21490#26126#32454
      OnClick = N1Click
    end
  end
end
