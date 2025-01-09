<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

abstract class ExtendsAbstractNoBodyContract
{
    abstract public function foo(): void;
}

final class ExtendsAbstractNoBodyClass extends ExtendsAbstractNoBodyContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

abstract class ExtendsAbstractNoBodyContract
{
    abstract public function foo(): void;
}

final class ExtendsAbstractNoBodyClass extends ExtendsAbstractNoBodyContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    public function bar(): void
    {
        echo 'bar';
    }
}
?>
