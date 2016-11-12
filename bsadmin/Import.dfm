object frmImport: TfrmImport
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #23548#20837
  ClientHeight = 261
  ClientWidth = 518
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 29
    Width = 518
    Height = 232
    Align = alClient
    BevelInner = bvLowered
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 0
    object lbl3: TLabel
      Left = 4
      Top = 129
      Width = 39
      Height = 17
      Alignment = taCenter
      Caption = #25991#20214#21517':'
    end
    object spselectpath: TSpeedButton
      Left = 436
      Top = 123
      Width = 59
      Height = 25
      Caption = #27983#35272'....'
      Flat = True
      OnClick = spselectpathClick
    end
    object Label1: TLabel
      Left = 5
      Top = 164
      Width = 48
      Height = 17
      Caption = #24635#35760#24405#65306
    end
    object Label2: TLabel
      Left = 46
      Top = 183
      Width = 156
      Height = 17
      Caption = #27491#22312#23548#20837#26126#32454#65292#35831#31245#20399#12290#12290#12290
      Visible = False
    end
    object Label3: TLabel
      Left = 14
      Top = 82
      Width = 39
      Height = 17
      Alignment = taCenter
      Caption = #21305#37197#39033':'
      Visible = False
    end
    object edtExcelPath: TRzEdit
      Left = 50
      Top = 126
      Width = 380
      Height = 25
      TabOrder = 0
    end
    object chisbn: TCheckBox
      Left = 59
      Top = 83
      Width = 65
      Height = 17
      Caption = 'ISBN'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object chname: TCheckBox
      Left = 138
      Top = 83
      Width = 61
      Height = 17
      Caption = #20070#21517
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object chprice: TCheckBox
      Left = 217
      Top = 83
      Width = 59
      Height = 17
      Caption = #23450#20215
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object chpress: TCheckBox
      Left = 371
      Top = 83
      Width = 56
      Height = 17
      Caption = #20986#29256#31038
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object chpresscount: TCheckBox
      Left = 713
      Top = 35
      Width = 50
      Height = 17
      Caption = #29256#27425
      TabOrder = 5
      Visible = False
    end
    object chauthor: TCheckBox
      Left = 293
      Top = 83
      Width = 59
      Height = 17
      Caption = #20316#32773
      TabOrder = 6
    end
    object chtishi: TCheckBox
      Left = 31
      Top = 106
      Width = 137
      Height = 17
      Caption = #26032#24314#20070#30446#25552#31034
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
      TabOrder = 7
    end
    object Panel1: TPanel
      Left = 530
      Top = 164
      Width = 40
      Height = 24
      TabOrder = 8
      Visible = False
    end
    object cbselfma: TCheckBox
      Left = 433
      Top = 83
      Width = 61
      Height = 17
      Caption = #33258#32534#30721
      TabOrder = 9
    end
    object radiogroup: TRadioGroup
      Left = 14
      Top = 22
      Width = 399
      Height = 48
      Columns = 3
      ItemIndex = 0
      Items.Strings = (
        #20808#34892#32773#20986#24211#21333
        'yh'#20986#24211#21333
        'qc'#20986#24211#21333)
      TabOrder = 10
      OnClick = radiogroupClick
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 518
    Height = 29
    AutoResize = False
    AutoStyle = False
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = clSkyBlue
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    GradientColorStyle = gcsMSOffice
    ParentFont = False
    TabOrder = 1
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnImport
      BtnExit)
    object BtnImport: TRzToolButton
      Left = 4
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Import'
      DisabledIndex = 1
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #23548#20837#13'[F7]'
      OnClick = BtnImportClick
    end
    object BtnExit: TRzToolButton
      Left = 64
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      ImageIndex = 2
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
  end
  object opndlgExcelPath: TRzOpenDialog
    Filter = 'Excel '#25991#20214'|*.xls'
    Left = 672
    Top = 328
  end
  object dset: TADODataSet
    CommandText = 
      'select ID, ParentID,BookTypeName, PressID,ISBN, Name, Price, Bar' +
      'code, UserDefCode, Date, Author, PressCount, Unavailable, bigBoo' +
      'kTypeID, smallBookTypeID, TotalAmount, PresentNum, AbbreviatedNa' +
      'me, FullName from UV_PressAndBookCatalogQuery'
    Parameters = <>
    Left = 528
    Top = 320
  end
  object con1: TADOConnection
    Left = 656
    Top = 304
  end
  object aq: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select * from BS_OrderNote where 1 = 0')
    Left = 520
    Top = 304
  end
  object qry: TADOQuery
    Parameters = <>
    Left = 720
    Top = 184
  end
  object ds: TDataSource
    Left = 608
    Top = 384
  end
  object query: TADOQuery
    Parameters = <>
    Left = 656
    Top = 280
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
        Size = -1
        Value = Null
      end
      item
        Name = '@selfcode'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@newbook'
        DataType = ftInteger
        Direction = pdOutput
        Size = 10
        Value = Null
      end>
    Left = 432
    Top = 48
  end
  object comaddnote: TADOCommand
    CommandText = 'Import_Add_Note;1'
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
        Name = '@NtHeaderID'
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@BkcatalogID'
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Amount'
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Discount'
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Stgid'
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@StackName'
        DataType = ftString
        Size = 100
        Value = Null
      end>
    Left = 256
    Top = 160
  end
  object cn: TADOConnection
    Left = 536
    Top = 336
  end
end
