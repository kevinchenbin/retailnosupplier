object frmExcelImport: TfrmExcelImport
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'Excel'#23548#20837
  ClientHeight = 197
  ClientWidth = 586
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = True
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 17
  object lbl3: TLabel
    Left = 18
    Top = 141
    Width = 39
    Height = 17
    Alignment = taCenter
    Caption = #25991#20214#21517':'
  end
  object spselectpath: TSpeedButton
    Left = 445
    Top = 138
    Width = 44
    Height = 25
    Caption = '....'
    Flat = True
    OnClick = spselectpathClick
  end
  object Label1: TLabel
    Left = 18
    Top = 169
    Width = 48
    Height = 17
    Caption = #24635#35760#24405#65306
  end
  object Label2: TLabel
    Left = 72
    Top = 169
    Width = 180
    Height = 17
    Caption = #27491#22312#23548#20837#35746#21333#26126#32454#65292#35831#31245#20399#12290#12290#12290
    Visible = False
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 586
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
      BtnImport
      BtnAlignBottom
      BtnExit)
    object BtnImport: TRzToolButton
      Left = 4
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Import'
      DisabledIndex = 1
      GradientColorStyle = gcsSystem
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #23548#20837#13'[F7]'
      OnClick = BtnImportClick
    end
    object BtnExit: TRzToolButton
      Left = 124
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      GradientColorStyle = gcsSystem
      ImageIndex = 2
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 64
      Top = 0
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 5
      GradientColorStyle = gcsSystem
      ImageIndex = 4
      UseToolbarButtonSize = False
      UseToolbarVisualStyle = False
      VisualStyle = vsGradient
      Caption = #26368#23567#21270#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
  end
  object edtExcelPath: TRzEdit
    Left = 64
    Top = 138
    Width = 380
    Height = 25
    TabOrder = 1
  end
  object chisbn: TCheckBox
    Left = 16
    Top = 49
    Width = 89
    Height = 17
    Caption = 'ISBN'
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object chname: TCheckBox
    Left = 119
    Top = 49
    Width = 90
    Height = 17
    Caption = #20070#21517
    Checked = True
    Enabled = False
    State = cbChecked
    TabOrder = 3
  end
  object chprice: TCheckBox
    Left = 222
    Top = 49
    Width = 82
    Height = 17
    Caption = #23450#20215
    Checked = True
    State = cbChecked
    TabOrder = 4
  end
  object chpress: TCheckBox
    Left = 16
    Top = 72
    Width = 89
    Height = 17
    Caption = #20986#29256#31038
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
  object chpresscount: TCheckBox
    Left = 119
    Top = 72
    Width = 90
    Height = 17
    Caption = #29256#27425
    Checked = True
    State = cbChecked
    TabOrder = 6
  end
  object chamount: TCheckBox
    Left = 222
    Top = 72
    Width = 82
    Height = 17
    Caption = #25968#37327
    Checked = True
    Enabled = False
    State = cbChecked
    TabOrder = 7
  end
  object chauthor: TCheckBox
    Left = 318
    Top = 49
    Width = 79
    Height = 17
    Caption = #20316#32773
    Checked = True
    State = cbChecked
    TabOrder = 8
  end
  object chbk: TCheckBox
    Left = 411
    Top = 48
    Width = 97
    Height = 17
    Caption = #22791#27880
    Checked = True
    State = cbChecked
    TabOrder = 9
  end
  object chdiscount: TCheckBox
    Left = 318
    Top = 72
    Width = 79
    Height = 17
    Caption = #25240#25187
    Checked = True
    State = cbChecked
    TabOrder = 10
  end
  object Panel1: TPanel
    Left = 534
    Top = 140
    Width = 55
    Height = 20
    TabOrder = 11
    Visible = False
  end
  object chclass: TCheckBox
    Left = 504
    Top = 48
    Width = 97
    Height = 17
    Caption = #29677#32423
    TabOrder = 12
    Visible = False
  end
  object chxuexuao: TCheckBox
    Left = 411
    Top = 48
    Width = 79
    Height = 17
    Caption = #23398#26657#24207#21495
    TabOrder = 13
    Visible = False
  end
  object chxiaoqu: TCheckBox
    Left = 16
    Top = 95
    Width = 89
    Height = 17
    Caption = #26657#21306
    TabOrder = 14
    Visible = False
  end
  object chxueyuan: TCheckBox
    Left = 119
    Top = 95
    Width = 90
    Height = 17
    Caption = #23398#38498
    TabOrder = 15
    Visible = False
  end
  object chcourse: TCheckBox
    Left = 222
    Top = 95
    Width = 82
    Height = 17
    Caption = #35838#31243#21517#31216
    TabOrder = 16
    Visible = False
  end
  object chteacher: TCheckBox
    Left = 411
    Top = 95
    Width = 80
    Height = 17
    Caption = #20219#35838#25945#24072
    TabOrder = 17
    Visible = False
  end
  object chincode: TCheckBox
    Left = 318
    Top = 95
    Width = 79
    Height = 17
    Caption = #20869#37096#35782#21035#30721
    TabOrder = 18
    Visible = False
  end
  object chtelphone: TCheckBox
    Left = 504
    Top = 95
    Width = 81
    Height = 17
    Caption = #32852#31995#26041#24335
    TabOrder = 19
    Visible = False
  end
  object chtishi: TCheckBox
    Left = 411
    Top = 117
    Width = 175
    Height = 17
    Caption = #23548#20837#36807#31243#20013#24314#26032#20070#26159#21542#25552#31034
    Checked = True
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 20
  end
  object opndlgExcelPath: TRzOpenDialog
    Filter = 'Excel '#25991#20214'|*.xls'
    Left = 536
    Top = 224
  end
  object dset: TADODataSet
    CommandText = 
      'select ID, ParentID,BookTypeName, PressID,ISBN, Name, Price, Bar' +
      'code, UserDefCode, Date, Author, PressCount, Unavailable, bigBoo' +
      'kTypeID, smallBookTypeID, TotalAmount, PresentNum, AbbreviatedNa' +
      'me, FullName from UV_PressAndBookCatalogQuery'
    Parameters = <>
    Left = 448
    Top = 248
  end
  object con1: TADOConnection
    Left = 492
    Top = 152
  end
  object aq: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select * from BS_OrderNote where 1 = 0')
    Left = 480
    Top = 216
  end
  object qry: TADOQuery
    Parameters = <>
    Left = 440
    Top = 208
  end
  object ds: TDataSource
    Left = 508
    Top = 168
  end
  object query: TADOQuery
    Parameters = <>
    Left = 512
    Top = 200
  end
  object comAddcatalog: TADOCommand
    CommandText = 'USP_BS_Add_Catalogid;1'
    CommandType = cmdStoredProc
    Parameters = <
      item
        Name = '@return_value'
        DataType = ftInteger
        Direction = pdReturnValue
        Size = 10
        Value = Null
      end
      item
        Name = '@ISBN'
        Attributes = [paNullable]
        DataType = ftString
        Size = 20
        Value = Null
      end
      item
        Name = '@Name'
        Attributes = [paNullable]
        DataType = ftString
        Size = 100
        Value = Null
      end
      item
        Name = '@Price'
        Attributes = [paNullable]
        DataType = ftFloat
        Size = 10
        Value = Null
      end
      item
        Name = '@Author'
        Attributes = [paNullable]
        DataType = ftString
        Size = 10
        Value = Null
      end
      item
        Name = '@PressCount'
        Attributes = [paNullable]
        DataType = ftString
        Size = 100
        Value = Null
      end
      item
        Name = '@Press'
        Attributes = [paNullable]
        DataType = ftString
        Size = 50
        Value = Null
      end
      item
        Name = '@pressindex'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@barcode'
        DataType = ftString
        Size = 20
        Value = Null
      end
      item
        Name = '@newbook'
        DataType = ftInteger
        Direction = pdOutput
        Size = 10
        Value = Null
      end>
    Left = 484
    Top = 136
  end
end
